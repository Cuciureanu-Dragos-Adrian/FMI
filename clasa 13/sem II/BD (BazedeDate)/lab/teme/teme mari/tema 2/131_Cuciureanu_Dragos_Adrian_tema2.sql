-- Partea I

--1
select count (last_name)
from employees
where last_name like ('K%');

--2
select employee_id, last_name, first_name
from employees
where salary = (select min(salary) from employees);

--3
select distinct employee_id, last_name
from employees
where employee_id in (select manager_id from employees where department_id = 30);

--4
select employee_id, last_name,first_name,(select count(employee_id) 
                                        from employees d 
                                        where e.employee_id = d.manager_id) as "NR Subalterni"
from employees e;

--5
select employee_id, last_name, first_name
from employees
where last_name in (select last_name from employees group by last_name having count(last_name)>1);

--6
select department_id,department_name
from departments d
where 2<=(select count(distinct job_id) 
        from employees e 
        where e.department_id = d.department_id);


-- Partea II

--7
select p.prod_desc, o.qty
from orders_tbl o, products_tbl p
where o.prod_id = p.prod_id
and lower(prod_desc) like '%plastic%';

--8
select last_name as "Nume", 'angajat' as "Tip"
from employee_tbl
union
select cust_name as "Nume", 'client' as "Tip"
from customer_tbl;

--9
select distinct p.prod_desc
from orders_tbl o, products_tbl p
where  o.prod_id = p.prod_id 
and
o.sales_rep in( select op.sales_rep
                from products_tbl pp, orders_tbl op, employee_tbl ep
                where ep.emp_id = op.sales_rep
                and op.prod_id = pp.prod_id
                and lower(pp.prod_desc) like ('% p%'));

--10
select c.cust_name
from customer_tbl c, orders_tbl o
where c.cust_id = o.cust_id
and to_char(o.ord_date, 'DD') = '17';

--11
select e.last_name, e.first_name, nvl(ep.salary, 0) as "Salariu", nvl(ep.bonus, 0) as "Bonus"
from employee_tbl e, employee_pay_tbl ep
where e.emp_id = ep.emp_id 
and (select nvl(ee.salary, 0)
    from employee_pay_tbl ee
    where ee.emp_id = e.emp_id) < 32000
and (select nvl(eee.bonus*17, 0)
    from employee_pay_tbl eee
    where eee.emp_id = e.emp_id) < 32000;

--12
select e.last_name, nvl((select sum (o.qty)
                    from orders_tbl o
                    where o.sales_rep = e.emp_id), 0) as "Produse livrate"
from employee_tbl e
where (select sum (o.qty)
                    from orders_tbl o
                    where o.sales_rep = e.emp_id) > 50 
or nvl((select sum (o.qty)
                    from orders_tbl o
                    where o.sales_rep = e.emp_id), 0) = 0;
                    
--13
select e.last_name, ep.salary, (select max (o.ord_date)
                                from orders_tbl o
                                where o.sales_rep = e.emp_id) as "Ultima comanda"
from employee_tbl e, employee_pay_tbl ep
where e.emp_id = ep.emp_id
and nvl((select count (o.qty)
        from orders_tbl o
        where o.sales_rep = e.emp_id), 0) >= 2;

--14
select prod_desc
from products_tbl
where cost > (select avg(cost) 
                 from products_tbl);
                 
--15
select e.last_name, e.first_name, nvl(ep.salary, 0) as Salary, nvl(ep.bonus, 0) as Bonus, 
(select sum(salary) from employee_pay_tbl) as "Salariu total",
(select sum(bonus) from employee_pay_tbl) as "Bonus total"
from employee_tbl e, employee_pay_tbl ep
where e.emp_id = ep.emp_id;

--16
select e.city
from employee_tbl e
where (select count (o.qty)
        from orders_tbl o
        where o.sales_rep = e.emp_id) =  (select max( count (o.qty))
                                            from orders_tbl o
                                            group by o.sales_rep);
                                            
--17
select distinct e.emp_id, e.last_name,
(select count (o1.qty)
from orders_tbl o1
where o1.sales_rep = e.emp_id
and to_char (o1.ord_date, 'MON') = 'SEP') as "Septembrie",
(select count (o2.qty)
from orders_tbl o2
where o2.sales_rep = e.emp_id
and to_char (o2.ord_date, 'MON') = 'OCT') as "Octombrie"
from employee_tbl e, orders_tbl o
where e.emp_id = o.sales_rep;

--18
select c.cust_name, c.cust_city
from customer_tbl c
where (c.cust_address like '0%' or 
c.cust_address like '1%' or 
c.cust_address like '2%' or 
c.cust_address like '3%' or 
c.cust_address like '4%' or 
c.cust_address like '5%' or 
c.cust_address like '6%' or 
c.cust_address like '7%' or 
c.cust_address like '8%' or 
c.cust_address like '9%') 
and (select count (o.qty)
    from orders_tbl o
    where o.cust_id = c.cust_id) = 0;

--19
select e.emp_id, e.last_name, e.city, c.cust_id, c.cust_name, c.cust_city
from employee_tbl e, customer_tbl c, orders_tbl o
where e.city != c.cust_city
and o.sales_rep = e.emp_id
and o.cust_id = c.cust_id;


--20
select sum(salary)/count (emp_id) as "Media salariilor"
from employee_pay_tbl;

--21 a. functioneaza
--21 b. nu functioneaza, deoarece a fost selectat un tabel care nu exista (employee_id)

--22
select e.last_name, ep.pay_rate
from employee_tbl e, employee_pay_tbl ep
where e.emp_id = ep.emp_id
and ep.pay_rate > (select max(epp.pay_rate)
                    from employee_pay_tbl epp, employee_tbl ee
                    where epp.emp_id = ee.emp_id
                    and lower (ee.last_name) like '%ll%');







