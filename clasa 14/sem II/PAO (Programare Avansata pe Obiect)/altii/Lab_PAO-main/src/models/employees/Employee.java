package models.employees;
import interfaces.hasId;
import interfaces.persistentWithDb;
import services.EmployeeService;

import java.util.UUID;

public abstract class Employee implements Comparable<Employee>, hasId, persistentWithDb {
        protected String id;
        protected double salary;
        protected final String firstName;
        protected final String lastName;
        protected String managerId = null;

        protected Employee(double salary, String firstName, String lastName){
                this.id = UUID.randomUUID().toString();
                this.salary = salary;
                this.firstName = firstName;
                this.lastName = lastName;
        }

        protected Employee(double salary, String firstName, String lastName, String managerId){
                this(salary, firstName, lastName);
                this.managerId = managerId;
        }

        protected Employee(String id, double salary, String firstName, String lastName, String managerId){
                this(salary, firstName, lastName, managerId);
                this.id = id;
        }

        public double getSalary(){
                return salary;
        }

        public String getManagerId(){
                return managerId;
        }

        abstract void giveRaise();
        @Override
        public String toString() {
                try {
                        return getFullName() + " with id -  " + this.id + ((this.managerId != null)?
                        " and manager: " + EmployeeService.getById(this.managerId).getFullName() : "") + "\n\tThis employee's salary is " + this.salary;
                } catch (Exception e) { // manager with managerId does not exist
                        this.managerId = null;
                        return toString();
                }
        }

        // employees have a descending sort by salary
        @Override
        public int compareTo(Employee o) {
                if (this.salary == o.salary)
                        return 0;
                else if (this.salary > o.salary)
                        return -1;
                return 1;
        }
        public String getId(){
                return this.id;
        }

        public void setManagerId(String id){
                this.managerId = id;
        }

        public String getFullName(){
                return this.lastName + " " + this.firstName;
        }
}
