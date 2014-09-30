#include "Core/Util/FileWatcher.h"

dd::FileWatcher::FileWatcher(std::string rootPath)
{
	m_RootPath = rootPath;
	m_Worker = new Worker;
	m_Thread = boost::thread(m_Worker);
}

dd::FileWatcher::~FileWatcher()
{
	m_Thread.detach();
	if (m_Worker != nullptr)
	{
		delete m_Worker;
	}
}

void dd::FileWatcher::Watch(std::string path, FileEventCallback_t callback)
{
	m_Worker.Watch(path, callback);
}

std::string dd::FileWatcher::RootPath() const
{
	return m_RootPath.string();
}

void dd::FileWatcher::Worker::operator()()
{
	while (true)
	{
		m_Mutex.lock();
		for (auto &kv : m_FileCallbacks)
		{
			boost::filesystem::path path = kv.first;
			FileEventCallback_t& callback = kv.second;
			FileEventFlags flags = UpdateFileInfo(path);
			if (flags != FileEventFlags::None && callback != nullptr)
			{
				callback(path.string(), flags);
			}
		}
		m_Mutex.unlock();
		boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	}
}


void dd::FileWatcher::Worker::Watch(std::string path, FileEventCallback_t callback)
{
	m_Mutex.lock();
	boost::filesystem::path bpath(path);
	m_FileCallbacks[bpath] = callback;
	if (boost::filesystem::exists(bpath))
	{
		m_FileInfo[bpath] = GetFileInfo(bpath);
	}
	m_Mutex.unlock();
}

dd::FileWatcher::Worker::FileInfo dd::FileWatcher::Worker::GetFileInfo(boost::filesystem::path path)
{
	FileInfo fi;
	fi.Size = boost::filesystem::file_size(path);
	fi.Timestamp = boost::filesystem::last_write_time(path);
	return fi;
}

dd::FileWatcher::FileEventFlags dd::FileWatcher::Worker::UpdateFileInfo(boost::filesystem::path path)
{
	FileEventFlags flags = FileEventFlags::None;
	if (boost::filesystem::exists(path))
	{
		FileInfo fi = GetFileInfo(path);
		auto lastFileInfoIt = m_FileInfo.find(path);
		if (lastFileInfoIt != m_FileInfo.end())
		{
			FileInfo lastFileInfo = lastFileInfoIt->second;

			if (fi.Size != lastFileInfo.Size)
			{
				LOG_DEBUG("FileWatcher: \"%s\" size changed!", path.string().c_str());
				flags = flags | FileEventFlags::SizeChanged;
			}
			if (fi.Timestamp != lastFileInfo.Timestamp)
			{
				LOG_DEBUG("FileWatcher: \"%s\" timestamp changed!", path.string().c_str());
				flags = flags | FileEventFlags::TimestampChanged;

			}
		}
		else
		{
			LOG_DEBUG("FileWatcher: \"%s\" was created!", path.string().c_str());
			flags = flags | FileEventFlags::Created;
		}
		m_FileInfo[path] = GetFileInfo(path);
	}
	else
	{
		auto fileInfoIt = m_FileInfo.find(path);
		if (fileInfoIt != m_FileInfo.end())
		{
			m_FileInfo.erase(fileInfoIt);
			LOG_DEBUG("FileWatcher: \"%s\" was deleted!", path.string().c_str());
			flags = flags | FileEventFlags::Deleted;
		}
	}
	return flags;
}
