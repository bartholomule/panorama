namespace panorama
{
	namespace Test
	{
		struct CopyCounter
		{
			CopyCounter() { ++CopyCounter::construct_count; }
			~CopyCounter() { ++CopyCounter::destruct_count; }
			CopyCounter(const CopyCounter& copy) { ++CopyCounter::copy_count; }
			CopyCounter& operator=(const CopyCounter& copy) { ++CopyCounter::assign_count; return *this; }

			static int construct_count;
			static int copy_count;
			static int destruct_count;
			static int assign_count;

			static void resetCounts();
		};
	}
}
