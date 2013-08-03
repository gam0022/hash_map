#include <stdio.h>
#include <ruby.h>

ID id_at, id_new, id_to_a, id_aset;
VALUE ZERO, ONE;


/*
 *   h = {:a => 0, :b => 1, :c => 2} # => {:a=>0, :b=>1, :c=>2}
 *   h.map_to_hash{|a| a*2}          # => {:a=>0, :b=>2, :c=>4}
 *   h                               # => {:a=>0, :b=>1, :c=>2}
 */

static VALUE
rb_hash_collect(VALUE self)
{
  VALUE new_hash, ary;
  VALUE pear, key, val;
  long i;

  new_hash = rb_funcall(rb_cHash, id_new, 0);
  ary      = rb_funcall(self, id_to_a, 0 );

  for (i=0; i<RARRAY_LEN(ary); ++i) {
    pear = rb_funcall(ary,  id_at, 1, INT2FIX(i));
    key  = rb_funcall(pear, id_at, 1, ZERO);
    val  = rb_funcall(pear, id_at, 1, ONE);
    rb_funcall(new_hash, id_aset, 2, key, rb_yield(val));
  }

  return new_hash;
}


/*
 *   h = {:a => 0, :b => 1, :c => 2} # => {:a=>0, :b=>1, :c=>2}
 *   h.map_to_hash!{|a| a*2}         # => {:a=>0, :b=>2, :c=>4}
 *   h                               # => {:a=>0, :b=>2, :c=>4}
 */

static VALUE
rb_hash_collect_bang(VALUE self)
{
  VALUE ary;
  VALUE pear, key, val;
  long i;

  ary = rb_funcall(self, id_to_a, 0 );

  for (i=0; i<RARRAY_LEN(ary); ++i) {
    pear = rb_funcall(ary,  id_at, 1, INT2FIX(i));
    key  = rb_funcall(pear, id_at, 1, ZERO);
    val  = rb_funcall(pear, id_at, 1, ONE);
    rb_funcall(self, id_aset, 2, key, rb_yield(val));
  }

  return self;
}

void Init_hash_map(void)
{

  //
  // CONSTS
  //

  id_at   = rb_intern("at");
  id_new  = rb_intern("new");
  id_to_a = rb_intern("to_a");
  id_aset = rb_intern("[]=");

  ZERO = INT2FIX(0);
  ONE  = INT2FIX(1);


  rb_define_method(rb_cHash, "map_to_hash", rb_hash_collect, 0);
  rb_define_method(rb_cHash, "collect_to_hash", rb_hash_collect, 0);
  rb_define_method(rb_cHash, "map_to_hash!", rb_hash_collect_bang, 0);
  rb_define_method(rb_cHash, "collect_to_hash!", rb_hash_collect_bang, 0);
}







//
// 失敗作
//
//static VALUE
//rb_hash_collect_(VALUE hash)
//{
//  //printf("Hash#map_to_hash called\n");
//
//  char *name, *value;
//  char **env;
//  VALUE ary;
//  VALUE new_hash = rb_hash_new();
//  long i;
//
//  RETURN_SIZED_ENUMERATOR(hash, 0, 0, rb_env_size);
//
//  ary = rb_ary_new();
//  env = GET_ENVIRON(environ);
//  while (*env) {
//    char *s = strchr(*env, '=');
//    if (s) {
//      rb_ary_push(ary, env_str_new(*env, s-*env));
//      rb_ary_push(ary, env_str_new2(s+1));
//    }
//    env++;
//  }
//  FREE_ENVIRON(environ);
//
//  for (i=0; i<RARRAY_LEN(ary); i+=2) {
//    //rb_yield(rb_assoc_new(RARRAY_AREF(ary, i), RARRAY_AREF(ary, i+1)));
//    name  = RARRAY_AREF(ary, i);
//    value = rb_yield(RARRAY_AREF(ary, i+1));
//    env_aset(new_hash, name, value);
//  }
//
//  return new_hash;
//}
