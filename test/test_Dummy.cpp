#include <boost/test/unit_test.hpp>
#include <sbpl_spline_primitives/Dummy.hpp>

using namespace sbpl_spline_primitives;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    sbpl_spline_primitives::DummyClass dummy;
    dummy.welcome();
}
