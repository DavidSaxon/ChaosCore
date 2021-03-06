#include <arcanecore/test/ArcTest.hpp>

ARC_TEST_MODULE(config.Variant)

#include <json/json.h>

#include <arcanecore/config/Variant.hpp>
#include <arcanecore/config/visitors/Primitive.hpp>
#include <arcanecore/config/visitors/String.hpp>

namespace
{

//------------------------------------------------------------------------------
//                                     PROTO
//------------------------------------------------------------------------------

ARC_TEST_UNIT(language)
{
    arc::io::sys::Path v_path;
    v_path << "tests" << "data" << "config" << "variants" << "lang.json";
    arc::config::Variant v(v_path, "uk", true);

    ARC_TEST_MESSAGE("Checking default (uk) variants");
    ARC_CHECK_EQUAL(
        *v.get("hello_world", arc::config::UTF8StringV::instance()),
        "Hello world!"
    );
    ARC_CHECK_EQUAL(
        *v.get("number", arc::config::IntV<arc::int32>::instance()),
        12
    );
    ARC_CHECK_EQUAL(
        *v.get("sentence", arc::config::UTF8StringV::instance()),
        "This is a language variant."
    );
    ARC_CHECK_EQUAL(
        *v.get("nest.string", arc::config::UTF8StringV::instance()),
        "twelve"
    );
    ARC_CHECK_EQUAL(
        *v.get("nest.number", arc::config::IntV<arc::int32>::instance()),
        3
    );

    ARC_TEST_MESSAGE("Checking German (de) variants");
    v.set_variant("de");
    ARC_CHECK_EQUAL(
        *v.get("hello_world", arc::config::UTF8StringV::instance()),
        "Hallo Welt!"
    );
    ARC_CHECK_EQUAL(
        *v.get("number", arc::config::IntV<arc::int32>::instance()),
        1337
    );
    ARC_CHECK_EQUAL(
        *v.get("sentence", arc::config::UTF8StringV::instance()),
        "This is a language variant."
    );
    ARC_CHECK_EQUAL(
        *v.get("nest.string", arc::config::UTF8StringV::instance()),
        "zwölf"
    );
    ARC_CHECK_EQUAL(
        *v.get("nest.number", arc::config::IntV<arc::int32>::instance()),
        3
    );

    ARC_TEST_MESSAGE("Checking Korean (ko) variants");
    v.set_variant("ko");
    ARC_CHECK_EQUAL(
        *v.get("hello_world", arc::config::UTF8StringV::instance()),
        "세계 안녕하세요!"
    );
    ARC_CHECK_EQUAL(
        *v.get("number", arc::config::IntV<arc::int32>::instance()),
        12
    );
    ARC_CHECK_EQUAL(
        *v.get("sentence", arc::config::UTF8StringV::instance()),
        "이것은 언어 의 변종이다."
    );
    ARC_CHECK_EQUAL(
        *v.get("nest.string", arc::config::UTF8StringV::instance()),
        "열두"
    );
    ARC_CHECK_EQUAL(
        *v.get("nest.number", arc::config::IntV<arc::int32>::instance()),
        39
    );
}

} // namespace anonymous
