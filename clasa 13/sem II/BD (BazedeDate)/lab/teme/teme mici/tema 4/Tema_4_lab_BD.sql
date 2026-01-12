--Partea I - Laborator 7

--6 
select count(count(department_id)) as "Numar departamente"
from employees
group by department_id
having count(employee_id) > 15;

--16
select j.job_title, a.avgSal as "Salariu mediu", (j.max_salary + j.min_salary)/2 - a.avgSal as "Diferenta", a."Numar de angajati"
from jobs j,
(
    select e.job_id, avg(e.salary) as avgSal,
        count(e.employee_id) as "Numar de angajati"
    from employees e
    group by e.job_id
) a
where j.job_id = a.job_id;


--Partea II - Laborator 8

--3
select a.department_id, e.last_name, a.salary
from employees e, (select department_id, min(salary) salary
                    from employees
                    group by department_id) a
where e.salary = a.salary
and a.department_id is not null
order by 1;
                    
--4
select d.department_id, d.department_name, e.last_name
from departments d, employees e
where d.department_id = e.department_id
and e.hire_date = (select min(e1.hire_date)
                    from employees e1
                    where e1.department_id = e.department_id)
order by 1;

--9
select department_name
from departments d
where 1 not in (select 1
                from employees
                where department_id = d.department_id);


--14.1
select sum(e.salary) as "Suma salariilor"
from employees e, jobs j
where e.job_id = j.job_id
and lower(j.job_title) like 's%';

--14.2
select e.job_id, avg(e.salary)
from employees e
group by e.job_id
having max(e.salary) = (select max(salary)
                        from employees);

--14.3
select e.job_id, avg(e.salary)
from employees e, jobs j
where e.job_id = j.job_id
and lower(j.job_title) not like 's%'
group by e.job_id
having max(e.salary) != (select max(salary)
                        from employees);