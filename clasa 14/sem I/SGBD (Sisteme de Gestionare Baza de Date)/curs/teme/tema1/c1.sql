





























































--delete + returning
declare
var_id_tc number;
var_col1_tc varchar(10);

begin
    delete from tabel_curs
    where id_tc between 1 and 2
    returning id_tc, col1
    into var_id_tc, var_col1_tc;
    
end;


--update + returning
declare
var_id_tc number;
var_col1_tc varchar(10);

begin
    update tabel_curs
    set col1 = 'col1'
    where id_tc between 1 and 2
    returning id_tc, col1
    into var_id_tc, var_col1_tc;
    
    commit;
    
end;






