set serveroutput on;

--5.1 se tine cont de durata cand a lucrat angajatul in departamentul curent
create or replace procedure p5_dac
as
nr number;
counter number;
zi varchar(20);

cursor c(dep_id departments.department_id%type) is
    select * 
    from (select to_char(hire_date, 'day'), count(*)
          from employees
          where department_id = dep_id
          group by to_char(hire_date, 'day')
          having count(*) = (select max(count(*))
                           from employees
                           where department_id = dep_id
                           group by to_char(hire_date, 'day')))
    where rownum < 2;
    
begin
    for dep in (select department_id, department_name from departments) loop
        
        dbms_output.new_line();
        dbms_output.put_line('Departamentul "' || dep.department_name || '" cu id-ul ' || dep.department_id || ':');
        
        select count(*)
        into nr
        from employees
        where department_id = dep.department_id;
        
        if nr = 0 then
            dbms_output.put_line('In departamentul "' || dep.department_name || '" nu lucreaza niciun angajat!');
        else
            open c(dep.department_id);
            loop
                fetch c into zi, counter;
                exit when c%notfound;
                
                dbms_output.put_line('In departamentul "' || dep.department_name || '" s-au angajat ' || counter
                || ' angajati intr-o zi de ' || zi);
                
                for i in (select employee_id, last_name, first_name, hire_date, salary
                          from employees
                          where department_id=dep.department_id
                          and to_char(hire_date, 'day') = zi) loop

                    dbms_output.put_line(i.last_name || ' ' || i.first_name || 'are salariul ' ||i.salary
                    ||' si vechimea '|| floor(sysdate - i.hire_date) || ' zile');
                        
                end loop;
            end loop;
            close c;
        end if;
    end loop;
end p5_dac;
/

begin
    p5_dac();
end;
/




--5.2 se tine cont de toata durata cand a lucrat angajatul
create or replace procedure p5_dac
as
nr number;
counter number;
zi varchar(20);
min_date job_history.start_date%type;

cursor c(dep_id departments.department_id%type) is
    select * 
    from (select to_char(hire_date, 'day'), count(*)
          from employees
          where department_id = dep_id
          group by to_char(hire_date, 'day')
          having count(*) = (select max(count(*))
                           from employees
                           where department_id = dep_id
                           group by to_char(hire_date, 'day')))
    where rownum < 2;
    
begin
    for dep in (select department_id, department_name from departments) loop
        
        dbms_output.new_line();
        dbms_output.put_line('Departamentul "' || dep.department_name || '" cu id-ul ' || dep.department_id || ':');
        
        select count(*)
        into nr
        from employees
        where department_id = dep.department_id;
        
        if nr = 0 then
            dbms_output.put_line('In departamentul "' || dep.department_name || '" nu lucreaza niciun angajat!');
        else
            open c(dep.department_id);
            loop
                fetch c into zi, counter;
                exit when c%notfound;
                
                dbms_output.put_line('In departamentul "' || dep.department_name || '" s-au angajat ' || counter
                || ' angajati intr-o zi de ' || zi);
                
                for i in (select employee_id, last_name, first_name, hire_date, salary
                          from employees
                          where department_id=dep.department_id
                          and to_char(hire_date, 'day') = zi) loop
                    select count(*)
                    into nr
                    from job_history
                    where employee_id = i.employee_id;
                    
                    if nr > 0 then
                        select min(start_date)
                        into min_date
                        from job_history
                        where employee_id = i.employee_id
                        group by employee_id;
                        
                        dbms_output.put_line(i.last_name || ' '|| i.first_name || 'are salariul ' || i.salary 
                        || ' si vechimea ' || floor(sysdate - nvl(min_date, sysdate)) || ' zile');
                        
                    else
                        dbms_output.put_line(i.last_name || ' ' || i.first_name || 'are salariul ' ||i.salary
                        ||' si vechimea '|| floor(sysdate - i.hire_date) || ' zile');
                        
                    end if;
                end loop;
            end loop;
            close c;
        end if;
    end loop;
end p5_dac;
/

begin
    p5_dac();
end;
/




--6 am modificat prima varianta a exercitiului 5 (5.1)
create or replace procedure p6_dac
as
nr number;
counter number;
idx number;
zi varchar(20);
last_date job_history.start_date%type;

cursor c(dep_id departments.department_id%type) is
    select * 
    from (select to_char(hire_date, 'day'), count(*)
          from employees
          where department_id = dep_id
          group by to_char(hire_date, 'day')
          having count(*) = (select max(count(*))
                           from employees
                           where department_id = dep_id
                           group by to_char(hire_date, 'day')))
    where rownum < 2;
    
begin
    for dep in (select department_id, department_name from departments) loop
        
        dbms_output.new_line();
        dbms_output.put_line('Departamentul "' || dep.department_name || '" cu id-ul ' || dep.department_id || ':');
        
        select count(*)
        into nr
        from employees
        where department_id = dep.department_id;
        
        idx := 0;
        last_date := sysdate;
        
        if nr = 0 then
            dbms_output.put_line('In departamentul "' || dep.department_name || '" nu lucreaza niciun angajat!');
        else
            open c(dep.department_id);
            loop
                fetch c into zi, counter;
                exit when c%notfound;
                
                dbms_output.put_line('In departamentul "' || dep.department_name || '" s-au angajat ' || counter
                || ' angajati intr-o zi de ' || zi);
                
                for i in (select employee_id, last_name, first_name, hire_date, salary
                          from employees
                          where department_id=dep.department_id
                          and to_char(hire_date, 'day') = zi
                          order by hire_date asc) loop
                
                    if last_date <> i.hire_date then
                        last_date := i.hire_date;
                        idx := idx + 1;
                    end if;
                
                    dbms_output.put_line(idx || '. ' ||i.last_name || ' ' || i.first_name || 'are salariul ' ||i.salary
                    ||' si vechimea '|| floor(sysdate - i.hire_date) || ' zile');
                        
                end loop;
            end loop;
            close c;
        end if;
    end loop;
end p6_dac;
/

begin
    p6_dac();
end;
/