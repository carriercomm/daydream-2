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
		None				= 0,
		Created				= 1 << 0,
		SizeChanged			= 1 << 1,
		TimestampChanged	= 1 << 2,
		Deleted				= 1 << 3,
	};
	friend inline FileEventFlags operator|(FileEventFlags a, FileEventFlags b) { return static_cast<FileEventFlags>(static_cast<int>(a) | static_cast<int>(b)); }
	friend inline bool operator&(FileEventFlags a, FileEventFlags b) { return static_cast<int>(a) & static_cast<int>(b); }

	typedef std::function<void(std::string, FileEventFlags)> FileEventCallback_t;

	FileWatcher(std::string rootPath);
	~FileWatcher();

	void Watch(std::string path, FileEventCallback_t callback);
	std::string RootPath() const { return m_RootPath.string(); }

private:
	class Worker;

	boost::filesystem::path m_RootPath;
	boost::thread m_Thread;
	Worker* m_Worker = nullptr;
};

class FileWatcher::Worker
{
public:
	void operator()();
	void Watch(std::string path, FileEventCallback_t callback);

private:
	struct FileInfo
	{
		int Size;
		std::time_t Timestamp;
	};

	std::unordered_map<boost::filesystem::path, FileEventCallback_t> m_FileCallbacks;
	std::unordered_map<boost::filesystem::path, FileInfo> m_FileInfo;
	boost::mutex m_Mutex;

	FileInfo GetFileInfo(boost::filesystem::path path);
	FileEventFlags UpdateFileInfo(boost::filesystem::path path);
};

}