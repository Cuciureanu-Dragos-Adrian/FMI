package collections;

import database.DatabaseReadService;
import models.products.Product;

import java.util.List;

public class ProductsCollection extends CustomCollection<Product>{

    private static ProductsCollection object = null;

    private ProductsCollection(){
        super();
    }

    /** Factory method for the singleton class
     *
     * @return the singleton instance of this class
     */
    public static ProductsCollection getCollection() {
        if(object == null)
            object = new ProductsCollection();
        return object;
    }

    @Override
    public void readFromDb() throws Exception {
        List<Product> cars = DatabaseReadService.readCars();
        List<Product> merchandise = DatabaseReadService.readMerchandise();
        List<Product> utilityVehicles = DatabaseReadService.readUtilityVehicles();

        this.objectList.addAll(cars); //add objects to list
        this.objectIds.addAll(cars.stream().map(Product::getId).toList()); //add ids to id set

        this.objectList.addAll(merchandise);
        this.objectIds.addAll(merchandise.stream().map(Product::getId).toList());

        this.objectList.addAll(utilityVehicles);
        this.objectIds.addAll(utilityVehicles.stream().map(Product::getId).toList());
    }
}
