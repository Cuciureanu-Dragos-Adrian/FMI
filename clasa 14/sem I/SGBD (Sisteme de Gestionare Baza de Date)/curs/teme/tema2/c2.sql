set serveroutput on;


--lob blob


create table tabel_curs_blob
(
tc1_id number(10),
denumire1 varchar2(20),
large_binary blob
);

insert into tabel_curs_blob values(1, 'primul blob', empty_blob());
insert into tabel_curs_blob values(2, 'al doilea blob', empty_blob());

select * 
from tabel_curs_blob;

drop table tabel_curs_blob;

--lob clob

create table tabel_curs_clob
(
tc2_id number(10),
denumire2 varchar2(20),
large_char clob
);

insert into tabel_curs_clob values(1, 'primul clob', 'hello');
insert into tabel_curs_clob values(2, 'al doilea clob', 'ооо');

select * 
from tabel_curs_clob;

drop table tabel_curs_clob;




DECLARE
    text clob := 'aaaaaaaaaaaaaaaa';

BEGIN
    DECLARE
    text clob := 'bbbbbbbbbb';

    BEGIN
        dbms_output.put_line ('text in subbloc: ' || text);
    END;

dbms_output.put_line ('text in bloc: ' || text);
END;

--lob nclob

create table tabel_curs_nclob
(
tc3_id number(10),
denumire3 varchar2(20),
large_natchar nclob
);

insert into tabel_curs_nclob values(1, 'primul nclob', 'hellooo00');
insert into tabel_curs_nclob values(2, 'al doilea nclob', 'оо??о');

select * 
from tabel_curs_nclob;

drop table tabel_curs_nclob;


DECLARE
    text nclob := 'cccccccc';

BEGIN
    DECLARE
    text nclob := 'dddddddddddddddddd';

    BEGIN
        dbms_output.put_line ('text in subbloc: ' || text);
    END;

dbms_output.put_line ('text in bloc: ' || text);
END;













