
#include "FileStream.hpp"
#include <cassert>

namespace XE {
    FileStream::FileStream(const std::string &fileName, const StreamFlags flags) {
        m_fileName = fileName;
        m_flags = flags;

        switch (flags) {
            case StreamFlags::Readable: 
                m_fileHandle = std::fopen(fileName.c_str(), "rb");
                break;
            
            case StreamFlags::Writtable: 
                m_fileHandle = std::fopen(fileName.c_str(), "ab");
                break;

            case StreamFlags::Both: 
                m_fileHandle = std::fopen(fileName.c_str(), "r+b"); 
                break;
        }

        assert(m_fileHandle);
    }

    FileStream::~FileStream() {}

    int FileStream::Read(void *buffer, const int size, const int count) {
        return std::fread(buffer, size, count, m_fileHandle);
    }

    int FileStream::Write(const void *buffer, const int size, const int count) {
        return std::fwrite(buffer, size, count, m_fileHandle);
    }

    bool FileStream::Seek(const int offset, const StreamOffset position) {
        switch (position) {
            case StreamOffset::Current:
                std::fseek(m_fileHandle, offset, SEEK_CUR);
                break;

            case StreamOffset::End:
                std::fseek(m_fileHandle, offset, SEEK_END);
                break;

            case StreamOffset::Set:
                std::fseek(m_fileHandle, offset, SEEK_SET);
                break;            
        }
    }

    int FileStream::Tell() const {
        return std::ftell(m_fileHandle);
    }

    StreamFlags FileStream::GetFlags() const {
        return m_flags;
    }
}