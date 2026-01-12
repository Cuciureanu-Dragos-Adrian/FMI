set serveroutput on;

drop table emp_dac;
create table emp_dac as select * from employees;

create or replace package tema7_dac
is
--a
    function get_id_job(nume jobs.job_title%type) return jobs.job_id%type;
    function get_id_dep(nume departments.department_name%type) return departments.department_id%type;
    function get_id_angajat(nume emp_dac.last_name%type, prenume emp_dac.first_name%type) return emp_dac.employee_id%type;
    function get_salariu_minim(id_dep emp_dac.department_id%type, id_job emp_dac.job_id%type) return emp_dac.salary%type;
    procedure adauga_angajat(nume emp_dac.last_name%type, prenume emp_dac.first_name%type, telefon emp_dac.phone_number%type, email emp_dac.email%type);
    
--b
    procedure muta_angajat(nume emp_dac.last_name%type, prenume emp_dac.first_name%type, nume_departament departments.department_id%type, nume_job jobs.job_title%type, nume_manager emp_dac.last_name%type, prenume_manager emp_dac.first_name%type);
    
--c
    function get_nr_subalterni(nume emp_dac.last_name%type, prenume emp_dac.first_name%type) return number;
    
--d
    procedure promoveaza_angajat(nume emp_dac.last_name%type, prenume emp_dac.first_name%type);
    
--e
    procedure modifica_salariu(nume emp_dac.last_name%type, salariu_nou emp_dac.salary%type);
    
--f
    cursor lista_angajati(id_job emp_dac.job_id%type) is
        select *
        from emp_dac
        where job_id = id_job;
    
--g
    cursor lista_joburi is
        select *
        from jobs;
    
--h
    procedure get_lista_joburi_si_angajati;
end;
/

create or replace package body tema7_dac
is
--a
--prima functie
    function get_id_job(nume jobs.job_title%type)
        return jobs.job_id%type is
        cod_job jobs.job_id%type;
        
    begin
        select job_id
        into cod_job
        from jobs
        where job_title = nume;

        return cod_job;
        
        exception
            when no_data_found then
                raise_application_error(-20000, 'nu exista job cu numele dat');
            when too_many_rows then
                raise_application_error(-20001, 'exista mai multe joburi cu numele dat');
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;

--a doua functie
    function get_id_dep(nume departments.department_name%type)
        return departments.department_id%type is
        cod_dep departments.department_id%type;
        
    begin
        select department_id
        into cod_dep
        from departments
        where department_name = nume;

        return cod_dep;
        
        exception
            when no_data_found then
                raise_application_error(-20000, 'nu exista departament cu numele dat');
            when too_many_rows then
                raise_application_error(-20001, 'exista mai multe departamente cu numele dat');
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;

--a treia functie
     function get_id_angajat(nume emp_dac.last_name%type, 
                             prenume emp_dac.first_name%type)
        return emp_dac.employee_id%type is
        id_angajat emp_dac.employee_id%type;
        
    begin
        select employee_id
        into id_angajat
        from emp_dac
        where first_name = prenume and last_name = nume;

        return id_angajat;
        
        exception
            when no_data_found then
                raise_application_error(-20000, 'nu exista angajati cu numele dat');
            when too_many_rows then
                raise_application_error(-20001, 'exista mai multi angajati cu numele dat');
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;

--a patra functie
    function get_salariu_minim(id_dep emp_dac.department_id%type, 
                               id_job emp_dac.job_id%type)
        return emp_dac.salary%type is
        minim emp_dac.salary%type;
        
    begin
        select min(salary) 
        into minim 
        from emp_dac 
        where department_id = id_dep 
        and job_id = id_job;
        
        return minim;
        
        exception
            when no_data_found then
                raise_application_error(-20000, 'nu exista un salariu minim');
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;

--procedura
    procedure adauga_angajat(nume emp_dac.last_name%type,
                             prenume emp_dac.first_name%type,
                             telefon emp_dac.phone_number%type,
                             email emp_dac.email%type)
    is
        emp_id emp_dac.employee_id%type;
        emp_hd emp_dac.hire_date%type;
        emp_job_id emp_dac.job_id%type;
        emp_dep_id emp_dac.department_id%type;
        emp_manager_id emp_dac.manager_id%type;
        emp_comission emp_dac.commission_pct%type;
        emp_salary emp_dac.salary%type;
        
    begin
        select max(employee_id) + 1
        into emp_id
        from emp_dac;

        emp_hd := sysdate;
        emp_comission := 0;
        emp_job_id := get_id_job('Sales Manager');
        emp_dep_id := get_id_dep('Accounting');
        emp_salary := get_salariu_minim(emp_dep_id, emp_job_id);
        emp_manager_id := get_id_angajat('Gee', 'Ki');

        insert into emp_dac (employee_id, first_name, last_name, email, phone_number, hire_date, job_id, salary, commission_pct, manager_id, department_id)
        values (emp_id, nume, prenume, email, telefon, emp_hd, emp_job_id, emp_salary, emp_comission, emp_manager_id, emp_dep_id);
        
        exception
            when no_data_found then
                raise_application_error(-20000, 'nu exista angajati cu numele dat');
            when too_many_rows then
                raise_application_error(-20001, 'exista mai multi angajati cu numele dat');
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;

--b
    procedure muta_angajat(nume emp_dac.last_name%type,
                           prenume emp_dac.first_name%type,
                           nume_departament departments.department_id%type,
                           nume_job jobs.job_title%type,
                           nume_manager emp_dac.last_name%type,
                           prenume_manager emp_dac.first_name%type)
    is
        emp_id emp_dac.employee_id%type;
        emp_manager_id emp_dac.manager_id%type;
        emp_department_id emp_dac.department_id%type;
        emp_job_id emp_dac.job_id%type;
        emp_salary emp_dac.salary%type;
        emp_new_salary emp_dac.salary%type;
        emp_hd emp_dac.hire_date%type;
        emp_comission emp_dac.commission_pct%type;
        
    begin
        emp_id := get_id_angajat(nume, prenume);
        
        select hire_date, job_id, department_id into emp_hd, emp_job_id, emp_department_id
        from emp_dac
        where employee_id = emp_id;
        
-- se adauga noul job in history
        insert into job_history(employee_id, start_date, end_date, job_id, department_id)
        values (emp_id, emp_hd, sysdate, emp_job_id, emp_department_id);
        
        emp_department_id := get_id_dep(nume_departament);
        emp_manager_id := get_id_angajat(nume_manager, prenume_manager);
        emp_job_id := get_id_job(nume_job);
        emp_new_salary := get_salariu_minim(emp_department_id, emp_job_id);

        select salary
        into emp_salary
        from emp_dac
        where employee_id = emp_id;

        select commission_pct
        into emp_comission
        from emp_dac
        where department_id = emp_department_id
        and job_id = emp_job_id;

        if(emp_salary < emp_new_salary) then
            emp_salary := emp_salary;
        end if;

        emp_hd := sysdate;

        update emp_dac
        set department_id = emp_department_id,
            job_id = emp_job_id,
            salary = emp_salary,
            commission_pct = emp_comission,
            hire_date = emp_hd
        where employee_id = emp_id;
        
        exception
            when no_data_found then
                raise_application_error(-20000, 'nu exista angajati cu numele dat');
            when too_many_rows then
                raise_application_error(-20001, 'exista mai multi angajati cu numele dat');
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;

--c
    function get_nr_subalterni(nume emp_dac.last_name%type, 
                               prenume emp_dac.first_name%type)
        return number is
        numar_subalterni number := 0;
        id_angajat emp_dac.employee_id%type;
        
    begin
        id_angajat := get_id_angajat(nume, prenume);
        
        for i in (select last_name as nume, first_name as prenume 
                from emp_dac 
                where manager_id = id_angajat) loop
            numar_subalterni := numar_subalterni + 1 + get_nr_subalterni(i.nume, i.prenume);
        end loop;

        return numar_subalterni;
        
        exception
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;

--d
    procedure promoveaza_angajat(nume emp_dac.last_name%type, 
                                 prenume emp_dac.first_name%type)
    is
        emp_id emp_dac.employee_id%type;
        emp_manager_id emp_dac.manager_id%type;
        emp_new_manager_id emp_dac.manager_id%type;
        
    begin
        emp_id := get_id_angajat(nume, prenume);
        
    select manager_id
    into emp_manager_id
    from emp_dac
    where employee_id = emp_id;
    
    if emp_manager_id is null then 
        dbms_output.put_line('angajatul este deja cel mai mare rank si nu mai paote fi promovat');
    else
    
    select manager_id
    into emp_new_manager_id
    from emp_dac
    where employee_id = emp_manager_id;
    
    update emp_dac
        set manager_id = emp_new_manager_id
        where employee_id = emp_id;
    
    end if;
    
    exception
            when no_data_found then
                raise_application_error(-20000, 'nu exista angajati cu numele dat');
            when too_many_rows then
                raise_application_error(-20001, 'exista mai multi angajati cu numele dat');
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;


--e
    procedure modifica_salariu(nume emp_dac.last_name%type, 
                               salariu_nou emp_dac.salary%type)
    is
        numar_aparitii number;
        emp_id emp_dac.employee_id%type;
        emp_job_id emp_dac.job_id%type;
        salariu_minim jobs.min_salary%type;
        salariu_maxim jobs.max_salary%type;
        
    begin
        select count(*)
        into numar_aparitii
        from emp_dac
        where last_name = nume;

        if (numar_aparitii = 0) then
            dbms_output.put_line('nu exista angajati cu acest nume!');

        elsif(numar_aparitii > 1) then
            dbms_output.put_line('mai multi angajati au acest nume!');

            for i in (select first_name, last_name from emp_dac where last_name = nume)
            loop
                dbms_output.put_line(i.last_name || ' ' || i.first_name);
            end loop;

        else
            select employee_id, job_id
            into emp_id, emp_job_id
            from emp_dac
            where last_name = nume;

            select min_salary, max_salary
            into salariu_minim, salariu_maxim
            from jobs
            where job_id = emp_job_id;

            if(salariu_nou > salariu_maxim or salariu_nou < salariu_minim) then
                dbms_output.put_line('salariul este in afara limitelor jobului');
            else
                update emp_dac
                set salary = salariu_nou
                where employee_id = emp_id;
            end if;
        end if;
        
        exception
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;

--h
    procedure get_lista_joburi_si_angajati is
        numar_aparitii number;
        stadiu_job varchar2(50);
        
    begin
        for job in lista_joburi loop
            dbms_output.new_line();
            dbms_output.put_line('se afiseaza jobul ' || job.job_title || ':');

            for angajat in lista_angajati(job.job_id) loop
                select count(*)
                into numar_aparitii
                from job_history
                where employee_id = angajat.employee_id;

                if(numar_aparitii > 1) then
                    stadiu_job := ' a mai avut acest job in trecut';
                else
                    stadiu_job := ' nu a mai avut acest job in trecut';
                end if;
                dbms_output.put_line(angajat.last_name || ' ' || angajat.first_name || stadiu_job);
            end loop;
        end loop;
        
        exception
            when others then
                raise_application_error(-20002, 'alta eroare!');
    end;
end;
/



--begin 
    --tema7_dac.adauga_angajat('parappa', 'wrappa', '0123.456.789', 'wrappa@pacpac');
    --tema7_dac.get_lista_joburi_si_angajati;
    --tema7_dac.promoveaza_angajat('King', 'Steven');
--end;
