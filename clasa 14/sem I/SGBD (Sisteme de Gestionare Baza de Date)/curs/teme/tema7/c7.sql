set serveroutput on;

--1

--where current of
declare
    cursor c is
        select employee_id
        from employees
        where department_id in (select department_id 
                                from departments 
                                where department_name = 'IT')
    for update of salary nowait;
 
    time_start timestamp;
    time_finish timestamp;
    
begin
    select localtimestamp into time_start
    from dual;
    
    for i in c loop
        update employees
        set salary = salary + 100
        where current of c;
    end loop;
 
    select localtimestamp into time_finish
    from dual;
 
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
    
    rollback;
end;
/
 
 
--rowid = i.rowid
declare
    cursor c is
        select employee_id, rowid
        from employees
        where department_id in (select department_id 
                                from departments 
                                where department_name = 'IT')
    for update of salary nowait;
 
    time_start timestamp;
    time_finish timestamp;
    
begin
    select localtimestamp into time_start
    from dual;
    
    for i in c loop
        update employees
        set salary = salary + 100
        where rowid = i.rowid;
    end loop;
 
    select localtimestamp into time_finish
    from dual;
 
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
    
    rollback;
end;
/

 
--bulk collect into
declare
    type tab_ind is table of employees%rowtype index by pls_integer;
    t tab_ind;
    time_start timestamp;
    time_finish timestamp;
    
begin
    select * bulk collect into t
    from employees
    where department_id in (select department_id 
                            from departments 
                            where department_name = 'IT');
    
    select localtimestamp into time_start
    from dual;
    
    forall i in 1..t.last
        update employees
        set salary = (salary*0.5)*2 + 199*0.95
        where t(i).employee_id = employee_id;
        
    select localtimestamp into time_finish
    from dual;
 
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
    
    rollback;
end;
/


-- varianta 1
select * 
from employees e
where exists (select 1 
            from departments d, job_history j
            where e.employee_id = j.employee_id
            and d.department_id = j.department_id
            and to_char(end_date,'q') = 1);
            
            
-- varianta 2
select * 
from employees e
where employee_id in (select employee_id
                    from departments d, job_history j
                    where e.employee_id = j.employee_id
                    and to_char(end_date,'q') = 1);


-- varianta 3
select distinct e.* 
from employees e, departments d, job_history j
where e.employee_id = j.employee_id
and d.department_id = j.department_id
and to_char(end_date,'q') = 1;




--cursor parametrizat
declare 
    numar_joburi number;
    counter number(5);
    titlu_job jobs.job_title%type;
    nume_angajat employees.first_name%type;
    salariu_angajat employees.salary%type;
    
    time_start timestamp;
    time_finish timestamp;
    
    type tip_joburi is table of jobs.job_id%type;
    joburi tip_joburi := tip_joburi();
    
    cursor c (job_curent jobs.job_id%type) is 
        select e.last_name, e.salary
        from employees e, jobs j
        where j.job_id = e.job_id 
        and j.job_id = job_curent;
        
begin
    select localtimestamp into time_start
    from dual;

    select count(*) into numar_joburi 
    from jobs;
    
    joburi.extend(numar_joburi);
    
    select j.job_id bulk collect into joburi 
    from jobs j;
    
    for i in joburi.first..joburi.last loop   
        select job_title
        into titlu_job
        from jobs j
        where j.job_id = joburi(i);
        
        --dbms_output.put_line(titlu_job || ':');
        counter := 0;
        
        open c(joburi(i));
        loop
            fetch c into nume_angajat, salariu_angajat;
            exit when c%notfound;
            --dbms_output.put_line(nume_angajat || ' ' || salariu_angajat);
            counter := counter + 1;
        end loop;
        close c;
        
        if counter = 0 then 
            dbms_output.put_line('Nu exista niciun angajat.');
        end if;
        
        --dbms_output.new_line();
    end loop;
    
    select localtimestamp into time_finish
    from dual;
    
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
end;
/


--cursor imbricat
declare 
    counter number;
    titlu_job jobs.job_title%type;
    nume_angajat employees.first_name%type;
    salariu_angajat employees.salary%type;
    
    time_start timestamp;
    time_finish timestamp;
    
    type refcursor is ref cursor;
    referinta_cursor refcursor;
    
    cursor c is 
        select j2.job_title, cursor
            (select e.last_name, e.salary
            from employees e, jobs j
            where j.job_id = e.job_id 
            and j.job_id = j2.job_id)
        from jobs j2;
        
begin
    select localtimestamp into time_start
    from dual;

    open c;
    loop
        fetch c into titlu_job, referinta_cursor;
        exit when c%notfound;
        
        --dbms_output.put_line(titlu_job || ':');
        counter := 0;
        
        loop 
            fetch referinta_cursor into nume_angajat, salariu_angajat;
            exit when referinta_cursor%notfound;
            
            --dbms_output.put_line(nume_angajat || ' ' || salariu_angajat);
            counter := counter + 1;
        end loop;
        
        if counter = 0 then 
            dbms_output.put_line('Nu exista niciun angajat.');
        end if;
        
        --dbms_output.new_line();
        
    end loop;
    close c;
    
    select localtimestamp into time_finish
    from dual;
    
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
end;
/
