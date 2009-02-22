#include "CopyCounter.hpp"

namespace panorama
{
	namespace Test
	{
		int CopyCounter::construct_count = 0;
		int CopyCounter::destruct_count = 0;
		int CopyCounter::copy_count = 0;
		int CopyCounter::assign_count = 0;

		void CopyCounter::resetCounts()
		{
			CopyCounter::construct_count = 0;
			CopyCounter::destruct_count = 0;
			CopyCounter::copy_count = 0;
			CopyCounter::assign_count = 0;
		}
	}
}
