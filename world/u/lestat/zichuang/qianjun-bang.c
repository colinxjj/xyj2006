//ǧ������
//lestat modi 2001 for dtxy

inherit SKILL;
#include <ansi.h>;
string* skill_head =({
        "$N�������ˣ�ʹ��һ��",
        "$N���쳤Ц����Ҳ������һ��",
        "$Nһ��������ʹ��",
        "$Nһ���޺ȣ���һ��",
        "$Nʹ��",
        "$N����������ƣ�һ��",

});

string* skill_tail =({
        "������$wӭ��һ��������$n��ͷ�������ҽ�����",
        "������һ����$n��ͷ����",
        "��Խ��$nͷ��������$w�ո���Բ��������һ������$n$l",
        "������$nһ�֮�䣬$N����$w���Ǻ�Х������ɨ��$n��$l",
        "���Ų����ԣ���һ������һ����\n���$n��æ���ң��мܲ���",
        "������$wת����糵һ�㣬\nһ�������Ӱ���л���$n����",
});

mapping *action = ({
        ([      "name":                 "�������޸�",
                "action":
"$N�������ˣ�����$wӭ��һ��������$n��ͷ�������ҽ�����",
                "dodge":                5,
     "parry":   -10,
                "damage":               45,
                "damage_type":  "����"
        ]),
        ([      "name":                 "̸Ц�����",
                "action":
"$N���쳤Ц����Ҳ������һ��"+HIY"��̸Ц�������"NOR+"������һ����$n��ͷ����",

                "dodge":                0,
     "parry":     0,
                "damage":               35,
                "damage_type":  "����"
        ]),
        ([      "name":                 "�¶�������",
                "action":
"$Nһ��������Խ��$nͷ��������$w�ո���Բ��������һ������$n$l",
                "dodge":                10,
     "parry":   -20,
                "damage":               45,
                "damage_type":  "����"
        ]),
        ([      "name":                 "�����Ͼ�¯",
                "action":
"$Nһ���޺ȣ���һ��"+HIW"�������Ͼ�¯��"NOR+"��\n����$nһ�֮�䣬$N����$w���Ǻ�Х������ɨ��$n��$l",
                "dodge":               10,
     "parry":   -15,
                "damage":               35,
                "damage_type":  "����"
        ]),
        ([      "name":                 "������һ�",
                "action":
"$Nʹ��"+HIB"��������һ᡹"NOR+"���Ų����ԣ���һ������һ����\n���$n��æ���ң��мܲ���",
                "dodge":                -5,
     "parry":     -5,
                "damage":               40,
                "damage_type":  "����"
        ]),   
        ([      "name":                 "����׹Ǿ�",
                "action":
"$N����������ƣ�����$wת����糵һ�㣬һ�������Ӱ���л���$n����",
                "dodge":                5,
     "parry":   -10,
                "damage":               50,
                "damage_type":  "����"
        ]),   
        ([      "name":                 "ǧ��������",
                "action":
"$N����$wһ������Ϊǧ���ϼ�⣬\n����$nĿѣ��ҡ֮ʱ����һ����ϼ����գ�\n$w�ѵ���$n��$l����һ���и����ã�����"+HIC"��ǧ�������"NOR+"",
                "dodge":                0,
                "parry":   -20,
                "damage":               55,
                "damage_type":  "����"
        ]),
   ([   "name":        "Ǭ��һ��",
     "action":   "$N������$wӭ��һ�ӣ��ó���ǧ��Ӱ�������������߾ٹ�����
$w��׼$n�����ž�������ȥ����һ��Ҫ�Ǵ��У����������޽���Ҳ����һ��",
     "parry":   -40,
     "dodge":   -70,
     "damage":   200,
     "force":   200,//������������force�˺�,��������
     "damage_type":  "����"
   ]),
});


int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 150 )
                return notify_fail("�������������û�а취��ǧ��������
����Щ���������ɡ�\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "stick" )
                return notify_fail("���������һ�����Ӳ�����������\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage=="stick"||usage=="parry";
}

mapping query_action(object me, object weapon)
{
   int i;
   mapping* m_actions;
   i=me->query_temp("QJB_perform");
   if( !me->query_temp("QJB_perform")) {
     if(me->query("skill_qianjun-bang")==0) return action[random(7)];
     if(random(2))return action[random(7)];
     m_actions=me->query("skill_qianjun-bang");
     return m_actions[random(sizeof(m_actions))];
   }else {
     return action[i];
   }
}


int practice_skill(object me)
{
        if( (int)me->query("kee") < 50
        ||      (int)me->query("force") < 5 )
                return notify_fail("�����������������û�а취��ϰǧ��������\n");
        me->receive_damage("kee", 30);
        me->add("force", -10);
        write("�㰴����ѧ����һ��ǧ��������\n");
        return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

string perform_action_file(string func)
{
return CLASS_D("puti") + "/qianjun-bang/" + func;
}

void skill_improved(object me)
{
   int m_skill=me->query_skill("qianjun-bang",1);       
   
   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"���ǧ��������������ˣ����ǧ����������һ���µľ��磡\n"NOR);
     if(me->query("zichuang/times")>7){
        tell_object(me,HIW"Ȼ����Ĺ����Ѿ��������壬�����ٴ��������ˡ�\n"NOR);
        return;
     }
     if(random(me->query("kar"))<20){
        tell_object(me,HIW"Ȼ��������о�Ȼ������һ��ʧ��У�\n"NOR);
        return;
     }
     if((random(me->query("int")/2)+(int)me->query_skill("literate")/50)<10){
       tell_object(me,HIW"Ȼ�������������һ�����ĸо����·���һ˿��Ҫ�Ķ���û��ץס��\n"NOR);
       return;
     }
     tell_object(me,HIW"��ͻȻ�������飬��ǧ�����������һ���µ��÷���\n"NOR);
     tell_object(me,"��Ϊ����ȡһ�����֣�");
     input_to( (: call_other, __FILE__, "name_skill", me:));
   }
   return;
}

void name_skill(object me, string arg)
{
  string *banned_name = ({
                "��", "��", "��", "��", "��", "��", "��", "��",
                "ү", "��", "��ʦ", "����", "����",
        });
   mapping* m_actions;
   mapping m_act=([]);
   int content, i=strlen(arg);
   string msg;

   m_actions=me->query("skill_qianjun-bang");
   if(!pointerp(m_actions))m_actions=({});
   
   content=me->query("str")+2*me->query_skill("unarmed",1)/10;
   m_act+=(["damage":content]);
   content=-me->query("spi");
   m_act+=(["dodge" :content]);
   content=-me->query("cps");
   m_act+=(["parry" :content]);
   content=me->query("con")+2*me->query_skill("force",1)/10;
   m_act+=(["force" :content]);
   m_act+=(["damage_type":"����"]);
if (!arg || arg=="") 
     {
          tell_object(me,"��Ϊ�������ʽȡһ�����֣�");
          input_to( (: call_other, __FILE__, "name_skill", me:));
          return;
     }
     else while(i--) 
     {
                if( arg[i]<=' ' ) 
                {
                        tell_object(me,"��ʽ���ֲ���ʹ�ÿ�����Ԫ���������趨һ�����֣�");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if(strsrch(arg, "��") >= 0) 
                {
                        tell_object(me,"��ʽ���ֲ����пո��������趨һ�����֣�");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if( i%2==0 && !is_chinese(arg[i..<0]) ) 
                {
                        tell_object(me,"�����á����ġ�Ϊ�������ʽȡ���֣�");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
     }
     if( member_array(arg, banned_name)!=-1 ) 
     {
     tell_object(me,"�Բ����������ֻ���������˵����š��������趨һ�����֣�");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
     if( (strlen(arg) < 8) || (strlen(arg) > 16 ) ) 
     {
     tell_object(me,"�Բ�����ʽ���ֱ����� �� �� �� �������֣�");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
//   if(!arg||arg==" ")arg="ǧ��������"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIG"��"+arg+"��"NOR
                  +skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_qianjun-bang",m_actions);
   me->add("zichuang/times",1);
}

