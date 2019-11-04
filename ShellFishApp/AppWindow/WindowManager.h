#pragma once
namespace controller
{

	class WindowManager
	{
	public:
		~WindowManager();
		WindowManager(WindowManager const&) = delete;
		void operator=(WindowManager const&) = delete;

		static WindowManager& getInstance();



	private:
		WindowManager();
	};
}