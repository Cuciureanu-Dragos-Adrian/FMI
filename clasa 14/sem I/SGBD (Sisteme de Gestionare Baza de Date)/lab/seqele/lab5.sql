set serveroutput on;

DECLARE
    v_cod employees.employee_id%TYPE;
    v_nume employees.last_name%TYPE;
    v_nr NUMBER(4);
    CURSOR c IS
        SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr
        FROM employees sef, employees ang
        WHERE ang.manager_id = sef.employee_id
        GROUP BY sef.employee_id
        ORDER BY nr DESC;
    top number(5) := 0;
    v_nr_anterior number(5) := -1;
    
BEGIN
    OPEN c;
    
    LOOP
        FETCH c INTO v_cod,v_nume,v_nr;
  
        if v_nr <> v_nr_anterior then
            top := top + 1;
        end if;
        
        v_nr_anterior := v_nr;
        
        EXIT WHEN top > 3 OR c%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('Managerul '|| v_cod ||' avand numele ' || v_nume ||' conduce ' || v_nr||' angajati');
    END LOOP;
    
    CLOSE c;
END;
/