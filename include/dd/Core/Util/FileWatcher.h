#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <functional>
#include <unordered_map>

namespace std
{
	template<> struct hash < boost::filesystem::path >
	{
		size_t operator()(const boost::filesystem::path& p) const
		{
			return boost::filesystem::hash_value(p);
		}
	};
}

namespace dd
{

class FileWatcher
{
public:
	enum class FileEventFlags
	{
		None = 0,
		Created = 1 << 0,
		SizeChanged = 1 << 1,
		DateChanged = 1 << 2,
		Deleted = 1 << 3,
	};
	friend inline FileEventFlags operator|(FileEventFlags a, FileEventFlags b) { return static_cast<FileEventFlags>(static_cast<int>(a) | static_cast<int>(b)); }
	friend inline bool operator&(FileEventFlags a, FileEventFlags b) { return static_cast<int>(a) & static_cast<int>(b); }


	typedef std::function<void(std::string, FileEventFlags)> FileEventCallback_t;

	FileWatcher(std::string rootPath)
	{
		m_RootPath = rootPath;
		m_Thread = boost::thread(boost::ref(m_Worker));
	}

	void Watch(std::string path, FileEventCallback_t callback)
	{
		m_Worker.Watch(path, callback);
	}

	std::string RootPath() const { return m_RootPath.string(); }

private:
	class Worker
	{
	public:
		void operator()()
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

		void Watch(std::string path, FileEventCallback_t callback)
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

	private:
		struct FileInfo
		{
			int Size;
			std::time_t DateModified;

			friend bool operator==(const FileInfo& lhs, const FileInfo& rhs)
			{
				return (lhs.Size == rhs.Size) && (lhs.DateModified == rhs.DateModified);
			}

			friend bool operator!=(FileInfo& lhs, FileInfo& rhs)
			{
				return !(lhs == rhs);
			}
		};

		std::unordered_map<boost::filesystem::path, FileEventCallback_t> m_FileCallbacks;
		std::unordered_map<boost::filesystem::path, FileInfo> m_FileInfo;
		boost::mutex m_Mutex;

		FileInfo GetFileInfo(boost::filesystem::path path)
		{
			FileInfo fi;
			fi.Size = boost::filesystem::file_size(path);
			fi.DateModified = boost::filesystem::last_write_time(path);
			return fi;
		}

		FileEventFlags UpdateFileInfo(boost::filesystem::path path)
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
					if (fi.DateModified != lastFileInfo.DateModified)
					{
						LOG_DEBUG("FileWatcher: \"%s\" timestamp changed!", path.string().c_str());
						flags = flags | FileEventFlags::DateChanged;

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
	};

	boost::filesystem::path m_RootPath;
	boost::thread m_Thread;
	Worker m_Worker;
};



}