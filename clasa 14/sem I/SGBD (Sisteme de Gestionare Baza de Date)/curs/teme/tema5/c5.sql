set serveroutput on;

--cerinta 1

--nested table sorted with bubble sort

declare
    type nested_tabel is table of integer;
    t nested_tabel := nested_tabel();
    var number;
    time_start timestamp;
    time_finish timestamp;
    
begin
    select localtimestamp into time_start
    from dual;
    
--populam colectia cu 1000 de numere random mai mici decat 1000
    for i in 1..10000 loop
        t.extend; 
        t(i) := dbms_random.value(0, 100);
    end loop;
    
--sortam elementele
    for i in t.first..t.last loop
        for j in (i+1)..t.last loop
            if t(i) > t(j) then 
                var := t(j);
                t(j) := t(i);
                t(i) := var;
            end if;
        end loop;
    end loop;
    
--afisam elementele colectiei
    dbms_output.put_line('colectia are ' || t.count || ' elemente:');
    
    for i in t.first..t.last loop
        dbms_output.put(t(i) || ' ');
    end loop;
    
    dbms_output.new_line;
    dbms_output.new_line;
    
--stergem elementele divizibile cu 3
    for i in t.first..t.last loop
        if t(i) mod 3 = 0 then
            t.delete(i);
        end if;
    end loop;
    
--afisam elementele colectiei updatate
    dbms_output.put_line('colectia are ' || t.count || ' elemente:');

    for i in t.first..t.last loop
        if t.exists(i) = true then
            dbms_output.put(t(i) || ' ');
        end if;
    end loop;
    
    dbms_output.new_line;
    dbms_output.new_line;
    
    select localtimestamp into time_finish
    from dual;
    
--afisam timpul de executie
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
end;




--index-by table sorted with bubble sort

declare
    type index_by_table is table of integer index by pls_integer;
    t index_by_table;
    var number;
    time_start timestamp;
    time_finish timestamp;
    
begin
    select localtimestamp into time_start
    from dual;

--populam colectia cu 1000 de numere random mai mici decat 1000
    for i in 1..10000 loop
        t(i) := dbms_random.value(0, 100);
    end loop;
    
--sortam elementele
    for i in t.first..t.last loop
        for j in (i+1)..t.last loop
            if t(i) > t(j) then 
                var := t(j);
                t(j) := t(i);
                t(i) := var;
            end if;
        end loop;
    end loop;
    
--afisam elementele colectiei
    dbms_output.put_line('colectia are ' || t.count || ' elemente:');
    
    for i in t.first..t.last loop
        dbms_output.put(t(i) || ' ');
    end loop;
    
    dbms_output.new_line;
    dbms_output.new_line;
    
--stergem elementele divizibile cu 3
    for i in t.first..t.last loop
        if t(i) mod 3 = 0 then
            t.delete(i);
        end if;
    end loop;
    
--afisam elementele colectiei updatate
    dbms_output.put_line('colectia are ' || t.count || ' elemente:');

    for i in t.first..t.last loop
        if t.exists(i) = true then
            dbms_output.put(t(i) || ' ');
        end if;
    end loop;
    
    dbms_output.new_line;
    dbms_output.new_line;
    
    select localtimestamp into time_finish
    from dual;
    
--afisam timpul de executie
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
end;




--varray sorted with bubble sort

declare
    type vector is varray(20001) of integer;
    t vector := vector();
    var number;
    c number := 0;
    time_start timestamp;
    time_finish timestamp;
begin
    select localtimestamp into time_start
    from dual;

--populam colectia cu 1000 de numere random mai mici decat 1000
    for i in 1..10000 loop
        t.extend;
        t(i) := dbms_random.value(0, 100);
    end loop;
    
--sortam elementele
    for i in t.first..t.last loop
        for j in (i+1)..t.last loop
            if t(i) > t(j) then 
                var := t(j);
                t(j) := t(i);
                t(i) := var;
            end if;
        end loop;
    end loop;
    
--afisam elementele colectiei
    dbms_output.put_line('colectia are ' || t.count || ' elemente:');
    
    for i in t.first..t.last loop
        dbms_output.put(t(i) || ' ');
    end loop;
    
    dbms_output.new_line;
    dbms_output.new_line;
    
--stergem elementele divizibile cu 3
    for i in t.first..t.last loop
        if t(i - c) mod 3 = 0 then
            for j in (i - c)..(t.last - 1) loop
                t(j) := t(j + 1);
            end loop;
            t.trim;
            c := c + 1;
        end if;
    end loop;
    
--afisam elementele colectiei updatate
    dbms_output.put_line('colectia are ' || t.count || ' elemente:');

    for i in t.first..t.last loop
        if t.exists(i) = true then
            dbms_output.put(t(i) || ' ');
        end if;
    end loop;
    
    dbms_output.new_line;
    dbms_output.new_line;
    
    select localtimestamp into time_finish
    from dual;
    
--afisam timpul de executie
    dbms_output.put_line ('execution time:' || (time_finish - time_start));
end;




--cerinta 2
drop table excursie_dac;

create or replace type tip_orase_dac is table of varchar2(100);
/
create table excursie_dac (cod_excursie    number(4) primary key not null,
                            denumire        varchar2(20),
                            orase           tip_orase_dac,
                            status          varchar2(20)
                            ) nested table orase store as tabel_orase_dac;



--a 5 inserari in tabel
insert into excursie_dac values (
    1,
    'Romania',
    tip_orase_dac('Bucuresti', 'Brasov', 'Cluj'),
    'disponibila'
);

insert into excursie_dac values (
    2,
    'Germania',
    tip_orase_dac('Munchen', 'Dortmund', 'Stuttgard'),
    'disponibila'
);

insert into excursie_dac values (
    3,
    'Franta',
    tip_orase_dac('Paris', 'Lion'),
    'disponibila'
);

insert into excursie_dac values (
    4,
    'Belgia',
    tip_orase_dac('Bruxel', 'Gent'),
    'disponibila'
);

insert into excursie_dac values (
    5,
    'Italia',
    tip_orase_dac('Roma', 'Florenta', 'Milano'),
    'anulata'
);

select * from excursie_dac;



--b.1 adaugati un oras nou, care va fi ultimul din lista
insert into table  (select orase
                    from excursie_dac
                    where cod_excursie = 1)
values('Iasi');

select * from excursie_dac;



--b.2 adaugati un oras nou, care va fi al doilea din lista
create table aux (id number(10), nume_oras varchar2(100));

insert into aux valueS (1,(select * from table (select orase
                                                    from excursie_dac
                                                    where cod_excursie = 1)
                                where rownum = 1));
insert into aux  valueS  (2, 'Sibiu');

update excursie_dac
set orase = (select cast (collect(nume_oras) as tip_orase_dac)
             from aux) multiset union  distinct (select orase 
                                                from excursie_dac 
                                                where cod_excursie = 1)
where cod_excursie = 1;
/

select * from excursie_dac;



--b.3 inversati ordinea a 2 orase specificate
update table (select orase 
             from excursie_dac 
             where cod_excursie = 1) a
set value(a) =  case
                    when column_value = 'Bucuresti' then 'Cluj'
                    when column_value = 'Cluj' then 'Bucuresti'
                    when column_value <> 'Bucuresti' and  column_value <> 'Cluj' then column_value
                end;

select * from excursie_dac;



--b.4 eliminati un oras specificat
delete from table (select orase
                   from excursie_dac
                   where cod_excursie = 1) a
where column_value = 'Brasov';

select * from excursie_dac;


--c pentru o excursie afisati numarul de orase si numele lor 
select cardinality(orase) Numar_orase_vizitate, orase
from excursie_dac
where cod_excursie = 1;



--d pentru fiecare excursie afisati orasele vizitate
select denumire, orase
from excursie_dac;



--e anulati excursiile cu cele mai putine orase vizitate
update excursie_dac
set status = 'anulata'
where cardinality(orase) =  (select min(Numar) 
                             from (select cardinality(orase) Numar, orase 
                                   from excursie_dac));

select * from excursie_dac;