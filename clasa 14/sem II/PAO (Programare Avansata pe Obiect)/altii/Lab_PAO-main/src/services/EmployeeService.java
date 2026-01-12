package services;

import collections.EmployeesCollection;
import models.employees.Employee;
import models.employees.Manager;
import models.employees.Mechanic;
import models.employees.Salesman;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class EmployeeService {

    private static final EmployeesCollection employees = EmployeesCollection.getCollection();

    /** Set an employee as a manager of the other employee
     *
     * @param employee - employee to which the manager will be set
     * @param manager - the manager
     * @throws Exception if one of the employees does not exist
     */
    private static void setManager(Employee employee, Employee manager) throws Exception {
        if(!employees.idExists(employee.getId()))
            throw new Exception("Employee does not exist");
        if(!employees.idExists(manager.getId()))
            throw new Exception("Manager does not exist");

        employee.setManagerId(manager.getId());
        employees.update(employee);
    }

    /** Computes and returns the direct subordinates of an employee
     *
     */
    private static List<Employee> getDirectSubordinates(Employee employee){
        List<Employee> result = new ArrayList<>();
        String empId = employee.getId();

        if(empId == null)
            return result;

        result = employees.getList().stream().filter((x) -> x.getManagerId() != null
                && x.getManagerId().equals(empId)).toList();

        return result;
    }

    /** Computes and returns a list of all of an employee's subordinates (recursively)
     *
     */
    private static List<Employee> getAllSubordinates(Employee employee){
        List<Employee> directSubordinates = getDirectSubordinates(employee);
        List<Employee> result = new ArrayList<>(directSubordinates);

        for(Employee subordinate : directSubordinates){ // for each direct subordinate
            List<Employee> recSubordinates = getAllSubordinates(subordinate);  // get all direct and indirect subordinates and add to result
            result.addAll(recSubordinates);
        }

        return result;
    }

    /** Get all the bosses - employees without managers
     *
     */
    private static List<Employee> getBosses(){
        return employees.getList().stream().filter((x) -> x.getManagerId() == null).toList();
    }

    /** Gets the employee with the highest salary.
     *
     * @throws Exception if there are no employees in the global list
     */
    private static Employee getEmployeeWithHighestSalary() throws Exception {
        if(employees.getList().size() == 0)
            throw new Exception("No employees exist!");
        return employees.getList().get(0); // list is sorted descending by salary, position 0 is the highest
    }

    /** Returns an employee with a given id.
     *
     * @param id - the id of the employee
     * @throws Exception if the id does not exist in the collection.
     */
    public static Employee getById(String id) throws Exception {
        return employees.getElementById(id);
    }

    public static void printAllEmployees() throws Exception {
        System.out.print("\nPrinting employees\n");
        printEmployeeList(employees.getList());
        AuditCsvService.writeLogToCsv("Printed-employees");
    }

    private static void printEmployeeList(List<Employee> list){
        for(int idx = 0; idx < list.size(); idx++){
            System.out.print((idx + 1) + ". " + list.get(idx) + "\n");
        }
    }

    /** Reads and creates a new Employee object.
     *
     */
    public static void readEmployee(Scanner scanner) throws Exception {
        System.out.println("Reading an employee\n");

        System.out.print("Please input the last name: ");
        String lastName = scanner.next().trim();
        System.out.print("Please input the first name: ");
        String firstName = scanner.next().trim();
        System.out.println("Please input the employee's salary:");
        double salary = Utilities.readDoubleInInterval(scanner, 0, Integer.MAX_VALUE);

        System.out.println("Please enter the type of employee - MA (Manager), ME (Mechanic), SA (Salesman): ");
        boolean notOk = true;
        String type;
        do{
            type = scanner.next().trim();
            if(!type.equals("MA") && !type.equals("ME") && !type.equals("SA")){
                System.out.println("Incorrect input! Please try again.");
                continue;
            }
            notOk = false;
        }while(notOk);

        if(type.equals("MA")) {
            //add new Manager to list
            employees.add(new Manager(salary, firstName, lastName));
            AuditCsvService.writeLogToCsv("Created-employee Manager");
        }
        else if(type.equals("ME")){
            //add new Mechanic to list
            employees.add(new Mechanic(salary, firstName, lastName));
            AuditCsvService.writeLogToCsv("Created-employee Mechanic");
        }
        else{
            employees.add(new Salesman(salary, firstName, lastName));
            AuditCsvService.writeLogToCsv("Created-employee Salesman");
        }
    }

    /** Prints all employee names along with every index in the employee collection.
     *
     */
    private static void printNamesAndIndexes(){
        for(int index = 0; index < employees.getList().size(); index++)
            System.out.print((index + 1) + ". " + employees.getList().get(index).getFullName() + "\n");
    }

    public static void deleteEmployee(Scanner scanner) throws Exception {
        System.out.println("Deleting an employee.\n");
        printNamesAndIndexes();
        System.out.print("Please enter an index to delete (or 0 to cancel): ");
        int toDeleteIndex = Utilities.readIntInInterval(scanner, 0, employees.getList().size());
        if(toDeleteIndex != 0){
            String employeeId = employees.getList().get(toDeleteIndex - 1).getId();
            employees.delete(employeeId); //subtract one because the printed list is 1-indexed
            System.out.println("Delete successful!");
            AuditCsvService.writeLogToCsv("Deleted-employee id - " + employeeId);
        }
    }

    /** Prompts the user to add a manager to an employee.
     *
     */
    public static void setManagerForEmployee(Scanner scanner) throws Exception {
        System.out.println("Setting a manager.\n");
        printNamesAndIndexes();
        System.out.print("Choose an employee for which to set a manager (or 0 to cancel): ");
        int employeeIndex = Utilities.readIntInInterval(scanner, 0, employees.getList().size());
        if(employeeIndex != 0) {
            System.out.print("Choose a manager (or 0 to cancel): ");
            int managerIndex = Utilities.readIntInInterval(scanner, 0, employees.getList().size());
            if(managerIndex != 0 && managerIndex != employeeIndex){
                setManager(employees.getList().get(employeeIndex - 1), employees.getList().get(managerIndex - 1));
            }
            AuditCsvService.writeLogToCsv("Set-manager employee - " + employees.getList().get(employeeIndex - 1).getId()
                                            + " manager - " + employees.getList().get(managerIndex - 1).getId());
        }
    }


    /** Prompts the user to choose an employee and prints the selected subordinates.
     *
     * @param type - type of subordinates to be printed. Should be 'direct' or 'all'
     */
    public static void printSubordinates(Scanner scanner, String type) throws Exception {
        System.out.println("Printing direct subordinates");
        printNamesAndIndexes();
        System.out.println("Select an employee for which to print direct subordinates.\n");
        int index = Utilities.readIntInInterval(scanner, 0, employees.getList().size());
        if(index != 0){
            Employee emp = employees.getList().get(index - 1);
            List<Employee> subordinates;

            if(type.equals("direct"))
                subordinates = getDirectSubordinates(emp);
            else if(type.equals("all"))
                subordinates = getAllSubordinates(emp);
            else{
                throw new Exception("Incorrect type!");
            }

            System.out.println((type.equals("direct")? "The direct":"All") + " subordinates of " + emp.getFullName() + " are:");

            printEmployeeList(subordinates);
            if(subordinates.size() == 0)
                System.out.println("\tThis employee has no subordinates.");
            AuditCsvService.writeLogToCsv("Printed-subordinates id - " + emp.getId());
        }
    }

    public static void printBosses() throws Exception{
        System.out.println("Printing all bosses (employees without a manager):");
        printEmployeeList(getBosses());
        AuditCsvService.writeLogToCsv("Printed-bosses");
    }

    public static void printEmployeeWithMaxSalary() throws Exception {
        System.out.println("Printing the employee that has the highest salary:");
        try {
            System.out.println(getEmployeeWithHighestSalary());
        }
        catch (Exception e){
            System.out.println("No employees exist!");
        }
        AuditCsvService.writeLogToCsv("Printed-employee-with-max-salary");
    }
}
