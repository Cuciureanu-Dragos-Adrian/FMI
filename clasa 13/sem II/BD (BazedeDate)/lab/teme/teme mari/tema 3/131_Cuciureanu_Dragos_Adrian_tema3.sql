-- Tema 3

--1
select s.s_id as "Cod", s.s_last as "Student sau curs", 'student' as "Tip"
from student s, faculty f
where s.f_id = f.f_id
and f.f_last = 'Brown'
union
select c2.course_no as "Cod", c2.course_name, 'curs' as "Tip"
from course_section c1, course c2, faculty f
where c1.course_no = c2.course_no
and c1.f_id = f.f_id 
and f.f_last = 'Brown';

--2
select s.s_id as Cod, s.s_last as Nume
from student s, enrollment e, course_section c1
where s.s_id = e.s_id
and e.c_sec_id = c1.c_sec_id
and (select c2.course_name
    from course c2
    where c1.course_no = c2.course_no) in 'Database Management'
and (select c2.course_name
    from course c2
    where c1.course_no = c2.course_no) not in 'Programming in C++';

--3
select distinct s.s_id as Cod, s.s_last as Nume
from student s, enrollment e
where s.s_id = e.s_id
and (e.grade = 'C' or e.grade is null);

--4
select l.loc_id, l.bldg_code, l.capacity
from location l
where l.capacity  = (select max(capacity)
                    from location);

--5
CREATE TABLE t (id NUMBER PRIMARY KEY);
INSERT INTO t VALUES(1);
INSERT INTO t VALUES(2);
INSERT INTO t VALUES(4);
INSERT INTO t VALUES(6);
INSERT INTO t VALUES(8);
INSERT INTO t VALUES(9);
commit;

select min(id)+1 as Minim, -1 as Maxim
from t
where id+1 not in (select id from t)
union
select -1 as Minim, max(id)-1 as Maxim
from t
where id-1 not in (select id from t)
order by 2;

--6
select f.f_id as "Cod profesor" , f.f_last as "Nume profesor",
(select decode(count(s.s_id), 0, 'Nu', 'Da ('||count(s.s_id)||')' )
from student s
where s.f_id = f.f_id) as "Student",
(select decode(count(cs.c_sec_id), 0, 'Nu', 'Da ('||count(cs.c_sec_id)||')' )
from course_section cs
where cs.f_id = f.f_id) as "Curs"
from faculty f;

--7
select t1.term_desc, t2.term_desc
from term t1, term t2
where t1.term_desc != t2.term_desc
and substr(t1.term_desc, 1, length(t1.term_desc)-1) = substr(t2.term_desc, 1, length(t2.term_desc)-1);

--8
select distinct s1.s_id as Cod, s1.s_last as Nume
from student s1, enrollment e1, course_section c1
where s1.s_id = e1.s_id
and e1.c_sec_id = c1.c_sec_id
and substr(to_char(c1.course_no), 5, 1) not in (select substr(to_char(c2.course_no), 5, 1)
                                                from student s2, enrollment e2, course_section c2
                                                where s2.s_id = e2.s_id
                                                and e2.c_sec_id = c2.c_sec_id
                                                and substr(to_char(c1.course_no), 5, 1) != substr(to_char(c2.course_no), 5, 1))
and (select count(c3.course_no)
    from student s3, enrollment e3, course_section c3
    where s3.s_id = e3.s_id
    and e3.c_sec_id = c3.c_sec_id
    and substr(to_char(c1.course_no), 5, 1) != substr(to_char(c3.course_no), 5, 1))>=1;


--9
select distinct cs1.course_no as x, cs2.course_no as y
from course_section cs1, course_section cs2
where cs1.term_id = cs2.term_id
and cs1.course_no > cs2.course_no
order by 1;

--10
select distinct cs.course_no, c.course_name, t.term_desc, cs.max_enrl
from course c, course_section cs, term t
where c.course_no = cs.course_no
and cs.term_id = t.term_id
and cs.max_enrl < (select min (cs2.max_enrl)
                    from course_section cs2, location l2
                    where cs2.loc_id = l2.loc_id
                    and l2.loc_id = 1);
                    
--11
select distinct c.course_name, cs.max_enrl
from course c, course_section cs
where c.course_no = cs.course_no
and cs.max_enrl = (select min (max_enrl)
                    from course_section)
order by 1;

--12
select f.f_last as Nume, (select avg(cs.max_enrl) 
                    from course_section cs
                    where cs.f_id = f.f_id) as "Medie numar locuri"
from faculty f;

--13
select f.f_last as Nume, (select count (s.s_id)
                            from student s
                            where s.f_id = f.f_id) as "Numar elevi coordonati"
                            from faculty f
where (select count (s.s_id)
        from student s
        where s.f_id = f.f_id) >= 3;
        
--14
select distinct c.course_name as Nume, (select max(capacity)
                                from location
                                where loc_id = cs.loc_id) as "Capacitate maxima", cs.loc_id as "Codul locatiei"
from course c, course_section cs
where c.course_no = cs.course_no;

--15
select t.term_desc, (select avg(cs.max_enrl)
                    from course_section cs
                    where cs.term_id = t.term_id) as "Numar mediu de locuri"
from term t
where t.term_desc like '%2007';





