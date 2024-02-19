#pragma once

#include <memory>
#include <vector>
#include "screen.h"

namespace game {

class Game;

enum Status {
	// Ok to process, don't remove
	Ok,
	// Don't process, don't remove
	Dangle,
	// Don't process, ok to remove
	Trash,
};

class Activity {
	protected:
		screen_::Point _point = screen_::Point(0, 0);
		Status _status = Status::Ok;

		inline static const std::string _EMPTY_SYMBOL = "";

	public:
		virtual ~Activity() = default;
		virtual void process(game::Game* g, screen_::Screen* s, char key) = 0;

		Activity() = default;
		Activity(screen_::Point point) noexcept;

		bool collided_with(Activity* activity) noexcept;
		screen_::Point& point() noexcept;

		Status status() const noexcept;
		void status(Status value) noexcept;

		virtual std::string symbol() noexcept;
		std::vector<std::string> symbol_lines() noexcept;
		size_t symbol_lines_count() noexcept;
};

class Game {
	protected:
		bool _need_to_quit = false;
		bool _is_over = false;
		std::vector<std::unique_ptr<Activity>> _activities;

	public:
		virtual ~Game() = default;
		virtual void restart() noexcept = 0;

		std::vector<std::unique_ptr<Activity>>& activities() noexcept;
		void add_activity(std::unique_ptr<Activity> a) noexcept;
		template<typename T>
		T* get_activity() const noexcept {
			const std::type_info& t_type_info = typeid(T);
			for (auto&& a: this->_activities) {
				if (typeid(*a.get()) == t_type_info) {
					return static_cast<T*>(a.get());
				}
			}
			return nullptr;
		}
		template<typename T>
		std::vector<T*> get_activities() const noexcept {
			std::vector<T*> rv;
			const std::type_info& t_type_info = typeid(T);
			for (auto&& a: this->_activities) {
				if (typeid(*a.get()) == t_type_info) {
					rv.push_back(static_cast<T*>(a.get()));
				}
			}
			return rv;
		}
		template<typename T>
		size_t get_activities_count() const noexcept {
			size_t rv = 0;
			const std::type_info& t_type_info = typeid(T);
			for (auto&& a: this->_activities) {
				if (typeid(*a.get()) == t_type_info) {
					++rv;
				}
			}
			return rv;
		}

		void over() noexcept;
		bool is_over() const noexcept;
		bool need_to_quit() const noexcept;
		void need_to_quit(bool value) noexcept;
		void process(screen_::Screen* screen, char key);
};

}
