#include <ruby.h>
#include <stdint.h>
#include <stdio.h>
#include <fuzzy.h>

#define ID_CONST_GET rb_intern("const_get")
#define CONST_GET(scope, constant) (rb_funcall(scope, ID_CONST_GET, 1, rb_str_new2(constant)))

#ifdef HAVE_RUBY_ENCODING_H

#include <ruby/io.h>
#define SSDEEP_RUBY_FILE_PATH(file) (RSTRING_PTR(RFILE(rb_io_taint_check(file))->fptr->pathv));

#else

#include <rubyio.h>
#define SSDEEP_RUBY_FILE_PATH(file) (RFILE(rb_io_taint_check(file))->fptr->path);

#endif

static VALUE cString_fuzzy_hash(VALUE self) {
  char *hash = (char *) malloc(FUZZY_MAX_RESULT);

  fuzzy_hash_buf((unsigned char *) RSTRING_PTR(self), RSTRING_LEN(self), hash);

  return rb_str_new(hash, strlen(hash));
}

static VALUE cString_fuzzy_compare(VALUE self, VALUE other) {
  char *self_hash = (char *) malloc(FUZZY_MAX_RESULT);
  char *other_hash = (char *) malloc(FUZZY_MAX_RESULT);

  fuzzy_hash_buf((unsigned char *) RSTRING_PTR(self), RSTRING_LEN(self), self_hash);
  fuzzy_hash_buf((unsigned char *) RSTRING_PTR(other), RSTRING_LEN(other), other_hash);

  return INT2NUM(fuzzy_compare(self_hash, other_hash));
}

static VALUE cFile_fuzzy_hash(VALUE self) {
  char *hash = (char *) malloc(FUZZY_MAX_RESULT);
  char *path;

  path = SSDEEP_RUBY_FILE_PATH(self);
  fuzzy_hash_filename(path, hash);

  return rb_str_new(hash, strlen(hash));
}

void Init_ssdeep_ruby_ext() {
  rb_define_method(rb_cString, "fuzzy_hash", cString_fuzzy_hash, 0);
  rb_define_method(rb_cString, "fuzzy_compare", cString_fuzzy_compare, 1);
  rb_define_method(rb_cFile, "fuzzy_hash", cFile_fuzzy_hash, 0);
}
