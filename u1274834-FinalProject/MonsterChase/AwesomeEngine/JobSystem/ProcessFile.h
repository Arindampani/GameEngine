//#pragma once
//#include <Windows.h>
//#include <conio.h>
//#include <iostream>
//#include <functional>
//#include <string>
//#include <assert.h>
//#include <vector>
//
//#include "JobSystem/JobSystem.h"
//#include "Syncronization/Events.h"
//namespace Engine {
//	class ProcessFile
//	{
//	public:
//		ProcessFile(const char* i_pFilename, std::function<void((const char *))> i_Processor, Engine::Event* i_pFinishEvent = nullptr) :
//			m_pFilename(i_pFilename),
//			m_Processor(i_Processor),
//			m_pFinishEvent(i_pFinishEvent)
//		{
//			assert(m_pFilename);
//		}
//
//		void operator() ()
//		{
//			if (m_pFilename)
//			{
//				size_t sizeFileContents = 0;
//				const char * pFileContents = LoadFile(m_pFilename, sizeFileContents);
//
//				if (pFileContents && sizeFileContents)
//				{
//					if (Engine::JobSystem::ShutdownRequested())
//					{
//						delete[] pFileContents;
//					}
//					else
//					{
//						std::cout << "ProcessFile finished loading file.\n";
//
//						// this works around C++11 issue with capturing member variable by value
//						std::function<void((const char *))> Processor = m_Processor;
//						Engine::Event* pFinishEvent = m_pFinishEvent;
//
//						Engine::JobSystem::RunJob("ProcessFileContents",
//							[pFileContents, sizeFileContents, Processor, pFinishEvent]()
//							{
//								ProcessFileContents(pFileContents, sizeFileContents, Processor, pFinishEvent);
//							},
//							"Default"
//								);
//
//					}
//				}
//			}
//		}
//
//		static const char * LoadFile(const char* i_pFilename, size_t& o_sizeFile)
//		{
//			assert(i_pFilename != NULL);
//
//			FILE* pFile = NULL;
//
//			errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
//			if (fopenError != 0)
//				return NULL;
//
//			assert(pFile != NULL);
//
//			int FileIOError = fseek(pFile, 0, SEEK_END);
//			assert(FileIOError == 0);
//
//			long FileSize = ftell(pFile);
//			assert(FileSize >= 0);
//
//			FileIOError = fseek(pFile, 0, SEEK_SET);
//			assert(FileIOError == 0);
//
//			const char* pBuffer = new char[FileSize];
//			assert(pBuffer);
//
//			size_t FileRead = fread(const_cast<char *> (pBuffer), 1, FileSize, pFile);
//			assert(FileRead == FileSize);
//
//			fclose(pFile);
//
//			o_sizeFile = FileSize;
//
//			return pBuffer;
//
//
//		}
//
//
//
//	private:
//		const char* m_pFilename;
//		std::function<void((const char *))>  m_Processor;
//		Engine::Event* m_pFinishEvent;
//	};
//
//
//	void PrintOnInterval(std::string i_String, unsigned int i_IntervalMilliseconds, unsigned int i_Count = 0)
//	{
//		bool bCounted = i_Count > 0;
//
//		do
//		{
//			std::cout << i_String << "\n";
//			Sleep(i_IntervalMilliseconds);
//		} while ((!bCounted || (bCounted && --i_Count)) && !Engine::JobSystem::ShutdownRequested());
//	}
//
//	void ProcessFileContents(const char * i_pFileContents, size_t i_sizeFileContents, std::function<void((const char *))> i_Processor, Engine::Event* i_pFinishEvent = nullptr)
//	{
//		if (i_pFileContents)
//		{
//			if (i_sizeFileContents && !Engine::JobSystem::ShutdownRequested())
//				i_Processor(i_pFileContents);
//
//			delete[] i_pFileContents;
//		}
//
//		std::cout << "ProcessFileContents finished processing file.\n";
//
//		if (i_pFinishEvent)
//			i_pFinishEvent->Signal();
//	}
//}
//
//
