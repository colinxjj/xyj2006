//by repoo

#include <ansi.h>
inherit ITEM;

void create()
{
  set_name(HIG"��ľ��"NOR, ({"famu gong"}));
  set_weight(800);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "һ��������С�ˡ�\n");
    set("unit", "��");
    set("material", "iron");
  }
  setup();
}