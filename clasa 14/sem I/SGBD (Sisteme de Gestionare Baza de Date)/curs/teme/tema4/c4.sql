set serveroutput on;

--nested table sorted with bubble sort

declare
    type tabel is table of integer;
    t tabel := tabel();
    var number;
    time_start timestamp;
    time_finish timestamp;
begin
    for i in 1..10000 loop
        t.extend; 
        t(i) := dbms_random.value(0, 1000);
    end loop;
    
    select localtimestamp into time_start
    from dual;
    
    for i in t.first..t.last loop
        for j in (i+1)..t.last loop
            if t(i) > t(j) then 
                var := t(j);
                t(j) := t(i);
                t(i) := var;
            end if;
        end loop;
    end loop;
    
--    for i in t.first..t.last loop
--        dbms_output.put(t(i) || ' ');
--    end loop;
--    
--    dbms_output.new_line;
    
    select localtimestamp into time_finish
    from dual;
    
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
end;





--nested table sorted with order by

create type tbl is table of integer
/
declare
    tabel tbl := tbl();
    idx number;
    time_start timestamp;
    time_finish timestamp;
begin
    for i in 1..10000 loop
        tabel.extend; 
        tabel(i) := dbms_random.value(0, 10000);
    end loop;

    select localtimestamp into time_start
    from dual;

    select cast ( multiset( select *
                          from table( tabel )
                          order by 1 asc ) as tbl)
    into tabel
    from dual;
    
--    for i in tabel.first..tabel.last loop
--        dbms_output.put(tabel(i) || ' ');
--    end loop;
--    
--    dbms_output.new_line;
    
    select localtimestamp into time_finish
    from dual;
    
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
end;






