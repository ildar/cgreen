#include <cgreen/cgreen.h>
#include <cgreen/internal/circular_buffer.h>

#ifdef __cplusplus
using namespace cgreen;
#endif

Describe(CircularBuffer);

static CircularBuffer* instance;
static const int length=100;

BeforeEach(CircularBuffer) {
    instance = create_circular_buffer(length);
}
AfterEach(CircularBuffer) {
    destroy_circular_buffer(instance);
}

Ensure(CircularBuffer, created_and_correctly_initialized) {
    assert_that(instance, is_non_null);
    assert_that(instance->buffer, is_non_null);
    assert_that(instance->buffer_end >= (instance->buffer + length));
    assert_that(instance->head, is_equal_to( instance->buffer ));
    assert_that(instance->tail, is_equal_to( instance->head ));
}

Ensure(CircularBuffer, accepts_data) {
    for(int i=0; i<length; i++)
        assert_that(write_to_circular_buffer(instance, i), is_equal_to(1));
    assert_that(write_to_circular_buffer(instance, 100), is_equal_to(0)); // full
}

Ensure(CircularBuffer, gives_data_back) {
    int c;
    for(int i=0; i<50; i++)
        write_to_circular_buffer(instance, i*2);
    for(int i=0; i<50; i++) {
        assert_that(read_from_circular_buffer(instance, &c), is_equal_to(1));
        assert_that(c, is_equal_to(i*2));
    }
    assert_that(read_from_circular_buffer(instance, &c), is_equal_to(0));
}

Ensure(CircularBuffer, is_really_circular) {
    int c;
    for(int i=1; i<16*length; i++) {
        for(int j=0; j<(length/2+3); j++)
            assert_that(write_to_circular_buffer(instance, i*j), is_equal_to(1));
        for(int j=0; j<(length/2+3); j++) {
            assert_that(read_from_circular_buffer(instance, &c), is_equal_to(1));
            assert_that(c, is_equal_to(i*j));
        }
        assert_that(read_from_circular_buffer(instance, &c), is_equal_to(0));
    }
}


TestSuite *circular_buffer_tests() {
    TestSuite *suite = create_test_suite();

    add_test_with_context(suite, CircularBuffer, created_and_correctly_initialized);
    add_test_with_context(suite, CircularBuffer, accepts_data);
    add_test_with_context(suite, CircularBuffer, gives_data_back);
    add_test_with_context(suite, CircularBuffer, is_really_circular);

    return suite;
}

/* vim: set ts=4 sw=4 et cindent: */
