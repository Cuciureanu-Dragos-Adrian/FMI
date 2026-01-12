set serveroutput on;

begin 
    for i in 1..100 loop
        insert into categorii values (i, 'inghetata', null);
    end loop;
end;
 
delete from categorii;

drop table categorii;

select * from categorii;

--cursor explicit
DECLARE
    TYPE tab_imb IS TABLE OF categorii%ROWTYPE;
    v_categorii tab_imb;
    time_start timestamp;
    time_finish timestamp;
     
    CURSOR c IS 
    SELECT * 
    FROM categorii 
    WHERE id_parinte IS NULL; 
BEGIN 
    select localtimestamp into time_start
    from dual;
    
    OPEN c;
    FETCH c BULK COLLECT INTO v_categorii;
    CLOSE c;
    FOR i IN 1..v_categorii.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_categorii(i).id_categorie || ' '|| v_categorii(i).denumire); 
    END LOOP; 
    
    select localtimestamp into time_finish
    from dual;
    
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
END;
/


--cursor implicit
DECLARE
    TYPE tab_imb IS TABLE OF categorii%ROWTYPE;
    v_categorii tab_imb; 
    time_start timestamp;
    time_finish timestamp;
BEGIN 
    select localtimestamp into time_start
    from dual;
    
    SELECT * BULK COLLECT INTO v_categorii
    FROM categorii
    WHERE id_parinte IS NULL;

    FOR i IN 1..v_categorii.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_categorii(i).id_categorie || ' '|| v_categorii(i).denumire); 
    END LOOP; 
    
    select localtimestamp into time_finish
    from dual;
    
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
END;
/





DECLARE
    TYPE tab_im IS TABLE OF countries%ROWTYPE;
    v_categorii tab_im;
     
    CURSOR c IS 
    SELECT * 
    FROM countries 
    WHERE region_id = 1; 
BEGIN 
    OPEN c;
    FETCH c BULK COLLECT INTO v_categorii;
    CLOSE c;
    FOR i IN 1..v_categorii.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_categorii(i).country_name); 
    END LOOP; 
END;
/


DECLARE
    TYPE tab_im IS TABLE OF countries%ROWTYPE;
    v_categorii tab_im; 
BEGIN 
    select * BULK COLLECT INTO v_categorii
    from countries
    where region_id = 1;

    FOR i IN 1..v_categorii.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_categorii(i).country_name); 
    END LOOP; 
END;
/


--limitarea numarului de linii incarcate
DECLARE
    TYPE tab_imb IS TABLE OF countries.country_name%TYPE;
    v_tari tab_imb;
    v_tari2 tab_imb;
    v_denumire countries.country_name%TYPE; 
     
    CURSOR c1 IS 
    SELECT country_name
    FROM countries
    WHERE ROWNUM <=10;
     
    CURSOR c2 IS 
    SELECT country_name
    FROM countries; 
 
BEGIN 
    OPEN c1;
    LOOP
    FETCH c1 INTO v_denumire;
    EXIT WHEN c1%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE(v_denumire);
    END LOOP; 
    CLOSE c1;
     
    DBMS_OUTPUT.PUT_LINE('----------------------');
     
    OPEN c2;
    FETCH c2 BULK COLLECT INTO v_tari LIMIT 10; 
    FETCH c2 BULK COLLECT INTO v_tari2 LIMIT 10; 
    CLOSE c2;
    
    FOR i IN 1..v_tari.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_tari(i));
    END LOOP; 
    
    FOR i IN 1..v_tari2.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_tari2(i));
    END LOOP;
END;
/

