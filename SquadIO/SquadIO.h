#pragma once
#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

namespace SquadIO {
	class SquadIO
	{
	public:

		static SQUADIO_API double Add(double a, double b);

	};
}


