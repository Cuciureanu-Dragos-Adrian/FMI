--Partea I - Laborator 9

--4
select c.country_name, count(*)
from countries c, locations l, departments d, employees e
where c.country_id = l.country_id
and l.location_id = d.location_id
and d.department_id = e.department_id
group by c.country_name;


--6
select e.employee_id, e.last_name, p.project_name
from employees e, works_on a, project p
where e.employee_id = a.employee_id (+)
and a.project_id = p.project_id (+);


--Partea II - Laborator 10

--10
create or replace force view viz_emp_salmax_dac ("name", "salary", "department", "max_salary") as
select e.last_name,  e.salary, d.department_name, (select max(salary)
                                                    from employees
                                                    where department_id = e.department_id)
from employees e, departments d
where e.department_id = d.department_id;

select * from viz_emp_salmax_dac;


--11
create or replace force view viz_sal_dac ("name", "department", "salary", "city") as
select e.last_name, d.department_name, e.salary, l.city
from employees e, departments d, locations l
where e.department_id = d.department_id
and d.location_id = l.location_id;

select * from viz_sal_dac;


--12 b
create or replace force view v_emp_dac ("employee_id", "first_name", "last_name", "email", "phone_number", unique ("email") disable, 
constraint "v_emp_dac_pk" primary key ("employee_id") disable) as 
select employee_id, first_name, last_name, email, phone_number 
from emp_dac;

select * from v_emp_dac;