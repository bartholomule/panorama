#define PROVIDE_AUTO_TEST_MAIN
#include "blocxx_test/CppUnit/AutoTest.hpp"
#include "panorama/common/StringDumpable.hpp"

AUTO_UNIT_TEST(string_dump_native)
{
	unitAssertEquals("1", panorama::toString(1));
	unitAssertEquals("3.1", panorama::toString(3.1));
	unitAssertEquals("abcd", panorama::toString("abcd"));
}

AUTO_UNIT_TEST(indent)
{
	panorama::Indentation indent("", "", "  ");
	unitAssertEquals("", indent.initial());
	unitAssertEquals("", indent.level());

	panorama::Indentation indent2 = indent.indent();
	unitAssertEquals("  ", indent2.initial());
	unitAssertEquals("  ", indent2.level());

	panorama::Indentation indent3 = indent2.indent();
	unitAssertEquals("    ", indent3.initial());
	unitAssertEquals("    ", indent3.level());
}

AUTO_UNIT_TEST(indentInside)
{
	panorama::Indentation indent("", "", "  ");
	unitAssertEquals("", indent.initial());
	unitAssertEquals("", indent.level());

	panorama::Indentation indent2 = indent.indentInside();
	unitAssertEquals("", indent2.initial());
	unitAssertEquals("  ", indent2.level());

	panorama::Indentation indent3 = indent2.indentInside();
	unitAssertEquals("", indent3.initial());
	unitAssertEquals("    ", indent3.level());

	panorama::Indentation indent4("  ", "  ", "  ");
	unitAssertEquals("  ", indent4.initial());
	unitAssertEquals("  ", indent4.level());

	panorama::Indentation indent5 = indent4.indentInside();
	unitAssertEquals("", indent5.initial());
	unitAssertEquals("    ", indent5.level());
}

AUTO_UNIT_TEST(string_dump_array)
{
	std::vector<int> arr(3);
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	unitAssertEquals("array\n{\n  1,\n  2,\n  3\n}", panorama::toString(arr, panorama::Indentation("", "", "  ")));
}

AUTO_UNIT_TEST(string_dump_array_of_arrays)
{
	panorama::Indentation indent("", "", "  ");
	std::vector<std::vector<int> > arr;
	for( int i = 1; i <= 3; ++i )
	{
		arr.push_back(std::vector<int>());
		for( int j = 1; j <= 3; ++j )
		{
			arr[i-1].push_back(i * j);
		}
	}
	blocxx::String expected =
"array\n\
{\n\
  array\n\
  {\n\
    1,\n\
    2,\n\
    3\n\
  },\n\
  array\n\
  {\n\
    2,\n\
    4,\n\
    6\n\
  },\n\
  array\n\
  {\n\
    3,\n\
    6,\n\
    9\n\
  }\n\
}";

	unitAssertEquals(expected, panorama::toString(arr, indent));
}

AUTO_UNIT_TEST(string_dump_array_ref)
{
	panorama::Indentation indent("", "", "  ");
	blocxx::Reference<std::vector<std::vector<int> > > arr(new std::vector<std::vector<int> >());
	for( int i = 1; i <= 3; ++i )
	{
		arr->push_back(std::vector<int>());
		for( int j = 1; j <= 3; ++j )
		{
			(*arr)[i-1].push_back(i * j);
		}
	}
	blocxx::String expected = blocxx::Format("(%1)->", reinterpret_cast<void*>(arr.getPtr())) +
"array\n\
  {\n\
    array\n\
    {\n\
      1,\n\
      2,\n\
      3\n\
    },\n\
    array\n\
    {\n\
      2,\n\
      4,\n\
      6\n\
    },\n\
    array\n\
    {\n\
      3,\n\
      6,\n\
      9\n\
    }\n\
  }";

	unitAssertEquals(expected, panorama::toString(arr, indent));
}

namespace
{
	class DumpMe : public panorama::StringDumpable
	{
	public:
		DumpMe(int b, int z) : bar(b), baz(z) { }
		void collectInternalMembers(panorama::MemberStringDumpCollector& collector) const
		{
			collector.addMember("bar", bar);
			collector.addMember("baz", baz);
		}

		blocxx::String name() const
		{
			return "DumpMe";
		}
	private:
		int bar;
		int baz;
	};

	class MoreToDump : public panorama::StringDumpable
	{
	public:
		MoreToDump(int b, int z) : dumpme(b,z) { }
		void collectInternalMembers(panorama::MemberStringDumpCollector& collector) const
		{
			collector.addMember("dumpme", dumpme);
		}

		blocxx::String name() const
		{
			return "MoreToDump";
		}
	private:
		DumpMe dumpme;
	};
}

AUTO_UNIT_TEST(dumpable)
{
	DumpMe foo(1,2);
	unitAssertEquals("DumpMe\n{\n  bar = 1;\n  baz = 2;\n}", foo.toString());

	DumpMe foo2(100,1000);
	unitAssertEquals("DumpMe\n{\n  bar = 100;\n  baz = 1000;\n}", foo2.toString());

	MoreToDump foo3(4,256);
	unitAssertEquals("MoreToDump\n{\n  dumpme = DumpMe\n    {\n      bar = 4;\n      baz = 256;\n    };\n}", foo3.toString());
}
