#pragma once
#include <stdint.h>
namespace Engine {
	class T;

	struct RefCount {
		uint64_t  SmartPtrs;
		uint64_t  WeakPtrs;

		RefCount(uint64_t i_SmartPtrs, uint64_t i_WeakPtrs) :
		SmartPtrs(i_SmartPtrs),
		WeakPtrs(i_WeakPtrs){

		}
	};
	

	template<class T>
	class WeakPointer;

	template<class T>
	class SmartPointer {


		template<class T>
		friend class WeakPointer;

	public:
		SmartPointer() :
			m_Object(nullptr),
			m_RefCount(nullptr)
		{}

		explicit SmartPointer(T * i_Object) :
			m_Object(i_Object),
			m_RefCount(i_Object ? new RefCount(1,0) : nullptr) {

		}


		explicit SmartPointer(const WeakPointer<T>& i_WeakPtr):
		m_Object(i_WeakPtr.m_Object),
		m_RefCount(i_WeakPtr.m_RefCount){

			if (m_RefCount) {

				if (m_RefCount->SmartPtrs == 0)
				{
					m_Object = nullptr;
					m_RefCount->SmartPtrs++;
				}
				else {
					m_RefCount->SmartPtrs++;
				}

			}

			

		}


		//create smart pointer from another pointer of diffrent type provided connected through inheritence
		template<class U>
		SmartPointer(SmartPointer<U>& i_Other) :
			m_Object(i_Other.m_Object),
			m_RefCount(i_Other.m_RefCount) {

			m_RefCount->SmartPtrs++;
		}

		SmartPointer(const SmartPointer<T>& i_Other) :
			m_Object(i_Other.m_Object),
			m_RefCount(i_Other.m_RefCount) {

			if (m_RefCount) {
				m_RefCount->SmartPtrs++;
			}
		}

		//move constructor in case forgot to pass by reference
		//SmartPointer(SmartPointer<T> && i_Other) noexcept :
		//	m_Object(i_Other.m_Object),
		//	m_RefCount(i_Other.m_RefCount) {

		//	i_Other.m_Object = nullptr;
		//	i_Other.m_RefCount = nullptr;
		//}

		SmartPointer<T>& operator=(const SmartPointer<T>& i_other) {
			if (this != &i_other) {

				Release();
				m_Object = i_other.m_Object;
				m_RefCount = i_other.m_RefCount;

				m_RefCount->SmartPtrs++;
			}
			return *this;
		}


		T * operator->() {

			return m_Object;
		}

		T & operator*() {
			return (*m_Object);
		}


		operator bool() {
			return m_Object != nullptr;
		}


		SmartPointer<T>& operator=(std::nullptr_t i_nullptr) {
			Release();
			RefCount = nullptr;
			T = nullptr;

			return *this;
		}

		~SmartPointer() {
			Release();
		}
		

	private:

		void Release() {
			if (m_RefCount)
			{
				if (--(m_RefCount->SmartPtrs) == 0) {
					delete m_Object;
					m_Object = nullptr;

					if (m_RefCount->WeakPtrs == 0)
					{
						delete m_RefCount;
						m_RefCount = nullptr;
					}
				}
			}

		}

		T * m_Object;
		RefCount * m_RefCount;
	
	};


	template<class T>
	class WeakPointer {

		template<class T>
		friend class SmartPointer;
	public:


		WeakPointer(const SmartPointer<T>& i_SmartPointer) :
			m_Object(i_SmartPointer.m_Object),
			m_RefCount(i_SmartPointer.m_RefCount) {

			m_RefCount->WeakPtrs++;
		}
		WeakPointer(WeakPointer<T>& i_Other) :
			m_Object(i_Other.m_Object),
			m_RefCount(i_Other.m_RefCount) {

			m_RefCount->WeakPtrs++;
		}

		WeakPointer<T>& operator=(WeakPointer<T>& i_other) {
			if (this != &i_other) {

				Release();
				m_Object = i_other.m_Object;
				m_RefCount = i_other.m_RefCount;

				m_RefCount->WeakPtrs++;
			}
		}


		SmartPointer<T> Acquire() {
			return SmartPointer<T>(*this);
		}

		operator bool() {

			return m_RefCount->SmartPtrs > 0;
		}

		WeakPointer<T> operator=(std::nullptr_t i_nullptr) {
			Release();

			m_RefCount = nullptr;
			T = nullptr;

			return *this;
		}

		~WeakPointer() {
			Release();
		}


	private:

		void Release() {

			if ((--m_RefCount->WeakPtrs) == 0 && (m_RefCount->SmartPtrs) == 0) {
				delete m_Object;
				delete m_RefCount;
				m_Object = nullptr;
				m_RefCount = nullptr;
			}

		}
		T* m_Object;
		RefCount* m_RefCount;

	};
}