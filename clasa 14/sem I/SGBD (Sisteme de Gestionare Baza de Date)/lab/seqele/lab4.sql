set serveroutput on;

-- 1
declare
    type vector is varray(5) of emp_dac.employee_id%type;
    ids vector;
    salariu_vechi number;
    salariu_nou number;
begin
    select employee_id bulk collect into ids
    from (select employee_id 
        from emp_dac 
        where commission_pct is null 
        order by salary)
    where rownum <= 5;
    
    for i in 1..5 loop
        select salary into salariu_vechi 
        from emp_dac 
        where employee_id = ids(i);
        
        update emp_dac 
        set salary = salary * 1.05 
        where employee_id = ids(i);
        
        select salary into salariu_nou 
        from emp_dac 
        where employee_id = ids(i);
        
        DBMS_OUTPUT.put_line('Salariu vechi: ' || salariu_vechi || ', Salariu nou: ' || salariu_nou);
    end loop;
    rollback;
end;

select salary 
from emp_dac
order by 1;


