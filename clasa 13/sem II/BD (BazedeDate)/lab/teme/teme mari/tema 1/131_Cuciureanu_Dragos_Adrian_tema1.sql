-- 131 Cuciureanu Dragos-Adrian tema 1

--GRILE:

--1  A
--2  C
--3  C
--4  C
--5  09-MAR-09
--6  3
--7  D


-- EXERCITII:

--1
select cust_id, cust_name
from customer_tbl
where cust_name like ('A%') or cust_name like ('B%')
and cust_state in ('IN', 'IL', 'OH', 'MI')
order by 2;

--2.1
select prod_id, prod_desc, cost
from products_tbl
where cost between 1 and 12.50;

--2.2
select prod_id, prod_desc, cost
from products_tbl
where cost not between 1 and 12.50;

--3
select lower(first_name) || '.' || lower(last_name) || '@ittech.com' as "Adresa"
from employee_tbl;

--4
select last_name || ', ' || first_name as "Nume", 
substr(emp_id, 1, 3) || '-' || substr(emp_id, 4, 2) || '-' || substr(emp_id, 6, 4) as "EMP_ID", 
'(' ||substr(phone, 1, 3) || ')' || substr(phone, 4, 3) || '-' || substr(phone, 6, 4) as "PHONE"
from employee_tbl;

--5
select emp_id, to_char (date_hire,'yyyy') as "hire_date"
from employee_pay_tbl;

--6
select e.emp_id, e.last_name, e.first_name, p.salary, p.bonus
from employee_tbl e, employee_pay_tbl p
where e.emp_id = p.emp_id;

--7
select c.cust_name, o.ord_num, o.ord_date
from customer_tbl c, orders_tbl o
where c.cust_id = o.cust_id
and c.cust_state like ('I%');

--8
select o.ord_num, o.qty, e.last_name, e.first_name, e.city
from orders_tbl o, employee_tbl e
where o.sales_rep = e.emp_id;

--9
select o.ord_num, o.qty, e.last_name, e.first_name, e.city
from orders_tbl o, employee_tbl e
where o.sales_rep(+) = e.emp_id;

--10
select emp_id, last_name
from employee_tbl
where middle_name is NULL;

--11
select e1.emp_id, e1.last_name, nvl2(e2.salary, e2.salary, 0) + nvl2(e2.bonus, e2.bonus, 0) as "Salariu anual"
from employee_tbl e1, employee_pay_tbl e2
where  e1.emp_id = e2.emp_id;

--12.1
select  e1.last_name || ' ' || e1.first_name as "Nume", nvl2(e2.salary, e2.salary, 0) as "Salariu", e2.position,
case
    when e2.position = 'MARKETING' then nvl2(e2.salary * 1.1, e2.salary * 1.1, 0)
    when e2.position = 'SALESMAN' then nvl2(e2.salary * 1.15, e2.salary * 1.15, 0)
    else nvl2(e2.salary, e2.salary, 0)
end as "Salariu modificat"
from employee_tbl e1, employee_pay_tbl e2
where  e1.emp_id = e2.emp_id;

--12.2
SELECT e1.FIRST_NAME || ' ' || e1.LAST_NAME as "Nume", nvl2(e2.salary, e2.salary, 0) as "Salariu", e2.POSITION, 
DECODE (e2.POSITION, 'MARKETING', nvl2(e2.salary * 1.1, e2.salary * 1.1, 0), 'SALESMAN', nvl2(e2.salary * 1.15, e2.salary * 1.15, 0), nvl2(e2.salary, e2.salary, 0)) "Salariu modificat"
FROM employee_tbl e1
JOIN employee_pay_tbl e2 ON(e1.EMP_ID = e2.EMP_ID);

--12.3
select e1.last_name || ' ' || e1.first_name as "Nume", nvl2(e2.salary, e2.salary, 0) as "Salariu", e2.position,
case e2.position
    when 'MARKETING' then nvl2(e2.salary * 1.1, e2.salary * 1.1, 0)
    when 'SALESMAN' then nvl2(e2.salary * 1.15, e2.salary * 1.15, 0)
    else nvl2(e2.salary, e2.salary, 0)
end as "Salariu modificat"
from employee_tbl e1, employee_pay_tbl e2
where  e1.emp_id = e2.emp_id;



