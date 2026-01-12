set serveroutput on;

--1 rezolvati problema in sql
select 
    case
        when count(e.employee_id) = 0 then 'In departamentul ' || d.department_name || ' nu lucreaza angajati'
        when count(e.employee_id) = 1 then 'In departamentul ' || d.department_name || ' lucreaza un angajat'
        else 'In departamentul ' || d.department_name || ' lucreaza ' || count(e.employee_id) || ' angajati'
    end as Departamente
from departments d, employees e
where d.department_id = e.department_id (+)
group by e.department_id, d.department_name;




--2.1 rezolvati problema folosind cursorul si o singura colectie
declare 
    type pair is record(nume departments.department_name%type, numar number(10));
    type table_pair is table of pair;
    t_pair table_pair;
    
    cursor c is
        select department_name nume, count(employee_id) nr 
        from departments d, employees e
        where d.department_id = e.department_id(+)
        group by department_name;
    
begin
    open c;
    fetch c bulk collect into t_pair limit 5;
     
    while t_pair.count <> 0
        loop
            for i in t_pair.first..t_pair.last loop
                if t_pair(i).numar = 0 then
                    dbms_output.put_line('In departamentul ' || t_pair(i).nume ||  ' nu lucreaza angajati');
                elsif  t_pair(i).numar = 1 then
                    dbms_output.put_line('In departamentul ' || t_pair(i).nume || ' lucreaza un angajat');
                else
                    dbms_output.put_line('In departamentul ' || t_pair(i).nume || ' lucreaza ' || t_pair(i).numar || ' angajati');
                end if;
            end loop;
                
            fetch c bulk collect into t_pair limit 5;
                
        end loop;
    close c;
end;



--2.2 rezolvati problema folosind doar colectii
declare 
    type pair is record(nume departments.department_name%type, numar number(10));
    type table_pair is table of pair;
    t_pair table_pair;
    idx_start number(10) := 1;
    idx_finish number(10);
    
begin
    select department_name nume, count(employee_id) nr 
    bulk collect into t_pair
    from departments d, employees e
    where d.department_id = e.department_id(+)
    group by department_name;
     
    while idx_start <= t_pair.count
        loop 
            if idx_start + 4 <= t_pair.count then
                idx_finish := 4;
            else 
                idx_finish := mod (t_pair.count, 5) - 1;
            end if;
            
            for i in idx_start..(idx_start + idx_finish) loop
                if t_pair(i).numar = 0 then
                    dbms_output.put_line('In departamentul ' || t_pair(i).nume ||  ' nu lucreaza angajati');
                elsif  t_pair(i).numar = 1 then
                    dbms_output.put_line('In departamentul ' || t_pair(i).nume || ' lucreaza un angajat');
                else
                    dbms_output.put_line('In departamentul ' || t_pair(i).nume || ' lucreaza ' || t_pair(i).numar || ' angajati');
                end if;
            end loop;
            
            idx_start := idx_start + idx_finish + 1;
        end loop;
end;
