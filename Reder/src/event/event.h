#pragma once

#include "reder/core.h"
#include "repch.h"




namespace reder {

	enum class eventType {
		None=0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum eventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static eventType getStaticType(){return eventType::##type;}\
							   virtual eventType getEventType() const override { return getStaticType(); } \
							   virtual const char* getName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlag() const override{return category;}

	class DLL_API event {
		friend class eventDispatcher;
	public:
		virtual eventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlag() const = 0;
		virtual std::string ToString() const{ return getName(); }

		inline bool isInCategory(eventCategory eventCategory) {
			return getCategoryFlag() & eventCategory;
		}
	protected:
		bool is_Handled = false;

	};

	class eventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		eventDispatcher(event& event)
			: m_Event(event){}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.getEventType() == T::getStaticType())
			{
				m_Event.is_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const event& e)
	{
		return os << e.ToString();
	}

}