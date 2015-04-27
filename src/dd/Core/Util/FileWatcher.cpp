#include "PrecompiledHeader.h"
#include "Core/Util/FileWatcher.h"

dd::FileWatcher::FileWatcher()
{
	m_Worker = new Worker;
}

dd::FileWatcher::FileWatcher(std::string rootPath)
{
	m_RootPath = rootPath;
	m_Worker = new Worker;
}

dd::FileWatcher::~FileWatcher()
{
	m_Thread.interrupt();
	if (m_Worker != nullptr)
	{
		delete m_Worker;
	}
}

void dd::FileWatcher::AddWatch(std::string path, FileEventCallback_t callback)
{
	m_Worker->AddWatch(path, callback);
}

void dd::FileWatcher::Start()
{
	m_Thread.interrupt();
	m_Thread = boost::thread(boost::ref(*m_Worker));
	m_IsRunning = true;
}

void dd::FileWatcher::Stop()
{
	m_Thread.interrupt();
	m_IsRunning = false;
}

void dd::FileWatcher::Check()
{
	m_Worker->Check();
}


void dd::FileWatcher::Worker::operator()()
{
	while (true)
	{
		boost::this_thread::interruption_point();
		Check();
		boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	}
}

void dd::FileWatcher::Worker::AddWatch(std::string path, FileEventCallback_t callback)
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

void dd::FileWatcher::Worker::Check()
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
