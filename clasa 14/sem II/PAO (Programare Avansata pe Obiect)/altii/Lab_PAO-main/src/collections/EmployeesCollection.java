package collections;

import database.DatabaseReadService;
import models.employees.Employee;

import java.util.List;
import java.util.Objects;

import models.employees.Manager;
import models.employees.Mechanic;
import models.employees.Salesman;

import javax.xml.crypto.Data;

public class EmployeesCollection extends CustomSortedCollection<Employee>{

    private static EmployeesCollection object = null;
    private EmployeesCollection(){
        super();
    }

    /** Factory method for the singleton class
     *
     * @return the singleton instance of this class
     */
    public static EmployeesCollection getCollection() {
        if(object == null)
            object = new EmployeesCollection();
        return object;
    }

    /** Also checks all employees for references of the current employee in the manager id.
     *
     */
    @Override
    public void delete(String id) throws Exception {

        if(!idExists(id))
            throw new Exception("Employee with id does not exist!");

        Employee toDelete = getElementById(id);

        for(Employee employee : this.objectList) {
            if(Objects.equals(employee.getManagerId(), id))
                employee.setManagerId(toDelete.getManagerId()); // get the manager of the manager
        }
        super.delete(id);
    }

    @Override
    public void readFromDb() throws Exception {
        List<Employee> managers = DatabaseReadService.readManagers();
        List<Employee> mechanics = DatabaseReadService.readMechanics();
        List<Employee> salesmen = DatabaseReadService.readSalesmen();

        this.objectList.addAll(managers); //add objects to list
        this.objectIds.addAll(managers.stream().map(Employee::getId).toList()); //add ids to id set

        this.objectList.addAll(mechanics);
        this.objectIds.addAll(mechanics.stream().map(Employee::getId).toList());

        this.objectList.addAll(salesmen);
        this.objectIds.addAll(salesmen.stream().map(Employee::getId).toList());

        super.readFromDb();
    }
}
