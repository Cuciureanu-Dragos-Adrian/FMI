set serveroutput on;


--1 no data found normal
drop table tabel_curs;

create table tabel_curs
(
id number(10),
nume varchar2(10),
salariu number(10)
);

insert into tabel_curs values (1, 'Bob', 1000);
commit;

select * from tabel_curs;

declare
    nume varchar(10);
    
begin
    select tc.nume into nume
    from tabel_curs tc
    where tc.id = 2;
    
    if nume is null then
        raise no_data_found;
    else
        dbms_output.put_line('Nume: ' || nume);
    end if;
    
    exception 
        when no_data_found then
            dbms_output.put_line('no data found');
end;




--2 no data found pe vectori
declare
    type tab_ind is table of number index by pls_integer;
    t    tab_ind;
    
begin
    for i in 1..10 loop
        t(i) := i;
    end loop; 
    
    dbms_output.put_line('element: ' || t(11));
    exception 
        when no_data_found then
            dbms_output.put_line('no data found');
end;













