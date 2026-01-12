-- tema 4

--1 
select s.s_last
from student s
where 1 not in (select 1 
                from enrollment e
                where s.s_id = e.s_id 
                and e.grade is not null);
                
--2
select distinct l.bldg_code
from location l
where not exists (select loc_id 
                    from course_section cs
                    where not exists (select loc_id
                                        from location l1
                                        where l1.loc_id = cs.loc_id
                                        and l.room = l1.room));
            
--3
select f.f_last
from faculty f
where exists (select s.s_id
                from student s, enrollment e
                where f.f_id = s.f_id
                and e.s_id = s.s_id
                and grade = 'A')
and exists (select 1
            from course_section cs, course c
            where cs.f_id = f.f_id
            and c.course_no = cs.course_no
            and course_name = 'Database Management');
            
--4
select f.f_last
from faculty f
where (select max(max_enrl)
        from course_section cs
        where cs.f_id = f.f_id) = (select max(max_enrl)
                                    from course_section cs)
or (select max(capacity)
    from location l, course_section cs
    where l.loc_id = cs.loc_id
    and cs.f_id = f.f_id) = (select max(capacity)
                                    from location l);
                                    
--5
select f.f_last
from faculty f
where f.loc_id in (select loc_id
                from location 
                where capacity in (select min(capacity)
                                    from location))
and f.f_id in (select cs.f_id
                from course_section cs
                where cs.max_enrl in (select min(max_enrl)
                                    from course_section 
                                    where loc_id in (select loc_id
                                                    from location 
                                                    where capacity in (select max(capacity)
                                                                        from location))));

--6
with sali as (select loc_id
            from course_section
            where f_id in (select f_id
                            from faculty 
                            where f_last = 'Marx')),
locuri as (select cs.c_sec_id
            from course_section cs, enrollment e, student s
            where cs.c_sec_id = e.c_sec_id
            and e.s_id = s.s_id
            and s.s_last = 'Jones')
select (sum(l.capacity) + sum(max_enrl))/(count(l.loc_id) + count(cs.c_sec_id)) as Medie
from location l, course_section cs
where l.loc_id in (select * from sali)
and cs.c_sec_id in (select * from locuri);

--7
with locuri as (select l.loc_id
                from location l, course_section cs, course c
                where l.loc_id = cs.loc_id
                and cs.course_no = c.course_no
                and c.course_name like '%Systems%')
select l.bldg_code, avg(l.capacity) as Medie
from location l
where l.loc_id in (select * from locuri)
group by l.bldg_code;

--8
select avg(l.capacity) as "???? ?????????
?? ???? ???"
from location l
where l.loc_id in (select distinct l.loc_id
                    from location l, course_section cs, course c
                    where l.loc_id = cs.loc_id
                    and cs.course_no = c.course_no
                    and c.course_name like '%Systems%');

--9
with cursuri1 as (select course_name
                    from course
                    where lower(course_name) like '%java%')
select course_no, 
case when not exists (select course_name
                    from course
                    where  course_name in (select * from cursuri1))
                    then course_name
else (select * from cursuri1)
end
from course;

--10       
select distinct cs.course_no, c.course_name
from course_section cs, course c
where c.course_no = cs.course_no
and decode ((select count(1)
            from course_section cs1, location l
            where cs.c_sec_id = cs1.c_sec_id
            and cs1.loc_id = l.loc_id
            and l.capacity = 42), 0, 0, 1)+
decode((select count(1)
        from course_section cs2, faculty f
        where cs.c_sec_id = cs2.c_sec_id
        and cs2.f_id = f.f_id
        and lower(f_last) like 'brown'), 0, 0, 1)+
decode((select count (1)
        from course_section cs3, student s, enrollment e
        where cs.c_sec_id = cs3.c_sec_id
        and cs3.c_sec_id = e.c_sec_id
        and e.s_id = s.s_id
        and lower (s_last) like 'jones'
        and lower (s_first) like 'tammy'), 0, 0, 1)+
decode((select count (1)
        from course_section cs4, course c
        where cs.c_sec_id = cs4.c_sec_id
        and cs4.course_no = c.course_no
        and c.course_name like '%Database%'), 0, 0, 1)+
decode((select count(1)
        from course_section cs5, term t
        where cs.c_sec_id = cs5.c_sec_id
        and cs5.term_id = t.term_id
        and t.term_desc like '%2007%'), 0, 0, 1)>=3;

--11
select distinct t.term_desc 
from term t,course_section cs,course c
where t.term_id = cs.term_id
and cs.course_no = c.course_no
and cs.sec_num in (select max(cs.sec_num) 
                    from course_section cs,course c
                    where cs.course_no = c.course_no
                    and c.course_name like ('%Database%'));

--12
select e.grade, count(distinct s.s_id) as nr_aparitii
from student s, enrollment e
where s.s_id = e.s_id
group by e.grade
having count(distinct s.s_id) = (select max(count(distinct s.s_id))
                                from student s, enrollment e
                                where s.s_id = e.s_id
                                group by e.grade
                                having e.grade is not null);

--13
select t.term_desc, count(c.course_name) as nr_materii
from term t, course_section cs, course c
where t.term_id = cs.term_id
and cs.course_no = c.course_no
and c.credits = 3
group by t.term_desc
having count(c.course_name) = ((select max(count(c.course_name))
                                        from term t, course_section cs, course c
                                        where t.term_id = cs.term_id
                                        and cs.course_no = c.course_no
                                        and c.credits = 3
                                        group by t.term_desc));

--14
select l.room
from location l
where exists (select 1
            from  course_section cs, course c
            where cs.loc_id = l.loc_id
            and cs.course_no = c.course_no 
            and c.course_name = 'Programming in C++')
and exists (select 1
        from  course_section cs, course c
        where cs.loc_id = l.loc_id
        and cs.course_no = c.course_no 
        and c.course_name = 'Database Management');

 
--15
select bldg_code, count(room)
from location
group by bldg_code
having count(room) = 1;
