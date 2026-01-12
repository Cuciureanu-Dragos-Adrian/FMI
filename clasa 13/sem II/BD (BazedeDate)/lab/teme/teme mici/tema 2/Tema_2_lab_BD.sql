--14
create table emp0_dac as select * from employees where 1=0;
commit;
create table emp1_dac as select * from employees where 1=0;
commit;
create table emp2_dac as select * from employees where 1=0;
commit;
create table emp3_dac as select * from employees where 1=0;
commit;

insert first
    when department_id = 80 then
        into emp0_dac
    when salary < 5000 then
        into emp1_dac
    when salary between 5000 and 10000 then
        into emp2_dac
    else 
        into emp3_dac
    select * from employees;
commit;


--16
create table EMP_DAC as select * from employees;
insert into EMP_DAC select * from employees;

update emp_dac
set job_id = 'SA_REP'
where department_id = 80 and commission_pct is not null;

commit;
rollback;

select * from EMP_DAC;
delete emp_dac;

--18
select * from EMP_DAC
order by commission_pct;

update emp_dac
set salary = (select avg(salary) from emp_dac),
commission_pct = (select avg(commission_pct) from emp_dac)
where salary = (select min(salary) from emp_dac);

rollback;

--19
update emp_dac
set job_id = (select job_id from emp_dac where employee_id = 205),
department_id = (select department_id from emp_dac where employee_id = 205)
where employee_id = 114;

select * from EMP_DAC
order by 1;

rollback;

--21
delete from emp_dac
where commission_pct is NULL;

select * from EMP_DAC
order by commission_pct;

rollback;


--22
delete from emp_dac
where department_id not in (select department_id from emp_dac);

rollback;