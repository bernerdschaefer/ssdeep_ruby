#include <ruby.h>
#include <rubyio.h>
#include <version.h>
#include <stdint.h>
#include <stdio.h>
#include <fuzzy.h>

#define ID_CONST_GET rb_intern("const_get")
#define CONST_GET(scope, constant) (rb_funcall(scope, ID_CONST_GET, 1, rb_str_new2(constant)))

static VALUE cString_fuzzy_hash(VALUE self) {
  char *hash = (char *) malloc(FUZZY_MAX_RESULT);

  fuzzy_hash_buf((unsigned char *) RSTRING(self)->ptr, RSTRING(self)->len, hash);

  return rb_str_new(hash, strlen(hash));
}

static VALUE cString_fuzzy_compare(VALUE self, VALUE other) {
  char *self_hash = (char *) malloc(FUZZY_MAX_RESULT);
  char *other_hash = (char *) malloc(FUZZY_MAX_RESULT);

  fuzzy_hash_buf((unsigned char *) RSTRING(self)->ptr, RSTRING(self)->len, self_hash);
  fuzzy_hash_buf((unsigned char *) RSTRING(other)->ptr, RSTRING(other)->len, other_hash);

  return INT2NUM(fuzzy_compare(self_hash, other_hash));
}

static VALUE cFile_fuzzy_hash(VALUE self) {
  char *hash = (char *) malloc(FUZZY_MAX_RESULT);
  rb_io_t *fptr;
  FILE *file;

  fptr = RFILE(rb_io_taint_check(self))->fptr;

  file = fopen(fptr->path, "r");

  fuzzy_hash_file(file, hash);

  return rb_str_new(hash, strlen(hash));
}

void Init_ssdeep_ruby_ext() {
  rb_define_method(rb_cString, "fuzzy_hash", cString_fuzzy_hash, 0);
  rb_define_method(rb_cString, "fuzzy_compare", cString_fuzzy_compare, 1);
  rb_define_method(rb_cFile, "fuzzy_hash", cFile_fuzzy_hash, 0);
}