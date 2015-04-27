#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <functional>
#include <unordered_map>

#include "Core/Util/Logging.h"

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
		enum class FileEventFlags;
		typedef std::function<void(std::string, FileEventFlags)> FileEventCallback_t;

		FileWatcher();
		FileWatcher(std::string rootPath);
		~FileWatcher();

		std::string RootPath() const { return m_RootPath.string(); }
		void AddWatch(std::string path, FileEventCallback_t callback);
		void Start();
		bool IsRunning() const { return m_IsRunning; }
		void Stop();
		void Check();

	private:
		class Worker;

		boost::filesystem::path m_RootPath;
		boost::thread m_Thread;
		Worker* m_Worker = nullptr;
		bool m_IsRunning = false;
	};

	enum class FileWatcher::FileEventFlags
	{
		None = 0,
		Created = 1 << 0,
		SizeChanged = 1 << 1,
		TimestampChanged = 1 << 2,
		Deleted = 1 << 3,
	};
	inline FileWatcher::FileEventFlags operator|(FileWatcher::FileEventFlags a, FileWatcher::FileEventFlags b) { return static_cast<FileWatcher::FileEventFlags>(static_cast<int>(a) | static_cast<int>(b)); }
	inline bool operator&(FileWatcher::FileEventFlags a, FileWatcher::FileEventFlags b) { return static_cast<int>(a)& static_cast<int>(b); }

	class FileWatcher::Worker
	{
	public:
		void operator()();
		void AddWatch(std::string path, FileEventCallback_t callback);
		void Check();

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