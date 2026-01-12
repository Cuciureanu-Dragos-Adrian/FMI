package services;

import collections.ProductsCollection;
import models.products.*;
import models.products.enums.CarType;
import models.products.enums.UtilityType;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class ProductService {

    private static final ProductsCollection products = ProductsCollection.getCollection();

    private static List<Product> getAllProducts(){
        return products.getList();
    }

    /** Set a new stock for a product.
     *
     * @throws Exception - if the product does not exist or the amount is incorrect
     */
    private static void setStock(Product product, int amount) throws Exception{
        if (!products.idExists(product.getId()))
            throw new Exception("Product does not exist!");

        if (Vehicle.class.isAssignableFrom(product.getClass())) { // if the product is a vehicle
            if (amount != 1)
                throw new Exception("Incorrect amount for vehicle derived class (must be 1).");
            products.delete(product.getId());
        } else { // the product is merchandise
            Merchandise prod = (Merchandise) product;
            if (amount < 0)
                throw new Exception("Amount must be at least 0.");

            prod.setStock(amount); //set stock
            products.update(prod);
        }

    }

    /** Modify the stock of a product - for merchandise subtract stock or for vehicles delete the vehicle
     *
     * @param product - product to be modified or deleted
     * @param amount - amount to subtract
     * @throws Exception - if the product does not exist or the amount is incorrect
     */
    public static void subtractStock(Product product, int amount) throws Exception {
        if (!products.idExists(product.getId()))
            throw new Exception("Product does not exist!");

        if (Vehicle.class.isAssignableFrom(product.getClass())) { // if the product is a vehicle
            if (amount != 1)
                throw new Exception("Incorrect amount for vehicle derived class (must be 1).");
            products.delete(product.getId());
        } else { // the product is merchandise
            Merchandise prod = (Merchandise) product;
            if (amount < 1)
                throw new Exception("Amount must be at least 1.");
            else if (amount > prod.getStock()) {
                throw new Exception("Amount must be less than or equal to the product's current stock");
            }
            prod.setStock(prod.getStock() - amount); //subtract required stock
            products.update(prod);
        }
    }

    /** Sets the discount of a product. Call with discount=0 to remove discount.
     *
     * @throws Exception if the product does not exist
     */
    private static void setDiscount(Product product, double discount) throws Exception {
        if (!products.idExists(product.getId()))
            throw new Exception("Product does not exist!");

        product.setDiscount(discount);
        products.update(product);
    }

    /** Searches for the Product of type Merchandise that has the highest stock.
     *
     * @return The merchandise item with the highest stock.
     * @throws Exception - there is no merchandise in the product list
     */
    private static Product getMerchandiseWithHighestStock() throws Exception {
        List<Product> merchandise = products.getList().stream().filter((x) -> x.getClass() == Merchandise.class).toList();
        if(merchandise.size() == 0)
            throw new Exception("No merchandise available!");

        int max = -1;
        Product maxStockMerch = null;
        for(Product merch : merchandise){ //search for max
            Merchandise aux = (Merchandise) merch;
            if(aux.getStock() > max){
                max = aux.getStock();
                maxStockMerch = merch;
            }
        }
        return maxStockMerch;
    }

    private static List<Product> getProductsOrderedByDiscount(){
        List<Product> result = getAllProducts();
        result.sort(Comparator.comparingDouble(Product::getDiscount));
        return result;
    }

    private static List<Product> getProductsOrderedByPrice(){
        List<Product> result = getAllProducts();
        result.sort(Comparator.comparingDouble(Product::getPrice).reversed());
        return result;
    }

    public static void printAllProducts() throws Exception {
        System.out.print("\nPrinting products\n");
        printProductList(products.getList());
        AuditCsvService.writeLogToCsv("Printed-products");
    }

    private static void printProductList(List<Product> list){
        for(int idx = 0; idx < list.size(); idx++){
            System.out.print((idx + 1) + ". " + list.get(idx) + "\n");
        }
    }

    /** Reads and creates a new Product object.
     *
     */
    public static void readProduct(Scanner scanner)throws Exception{
        System.out.println("Reading a product\n");

        System.out.print("Please input the product's name: \n");
        scanner.nextLine();
        String name = scanner.nextLine().trim();
        System.out.print("Please input the product's price: ");
        double price = Utilities.readDoubleInInterval(scanner, 0, Integer.MAX_VALUE);

        System.out.println("Please enter the type of product - ME (Merchandise), VE (Vehicle): ");
        boolean notOk = true;
        String type;
        do{
            type = scanner.next().trim();
            if(!type.equals("VE") && !type.equals("ME")){
                System.out.println("Incorrect input! Please try again.");
                continue;
            }
            notOk = false;
        }while(notOk);

        if(type.equals("ME")) {
            System.out.print("Please enter the stock:");
            int stock = Utilities.readIntInInterval(scanner, 0, Integer.MAX_VALUE);
            //add new Merchandise to list
            products.add(new Merchandise(name, price, stock));
            AuditCsvService.writeLogToCsv("Created-product Merchandise");
        }
        else{
            System.out.print("Please input the number of wheels:");
            int wheelNumber = Utilities.readIntInInterval(scanner, 3, 20);
            System.out.print("Please input the number of doors:");
            int doorNumber = Utilities.readIntInInterval(scanner, 1, 10);
            System.out.print("Please input the number of seats:");
            int seatNumber = Utilities.readIntInInterval(scanner, 1, 200);

            System.out.println("Please enter the type of vehicle - CA (Car), UV(Utility Vehicle)");

            notOk = true;
            do{
                type = scanner.next().trim();
                if(!type.equals("CA") && !type.equals("UV")){
                    System.out.println("Incorrect input! Please try again.");
                    continue;
                }
                notOk = false;
            }while(notOk);

            if (type.equals("CA")) {
                System.out.println("Please enter the type of car - SE (Sedan), CO (Coupe), SU (SUV), LI (Limousine)");
                notOk = true;
                do{
                    type = scanner.next().trim();
                    if(!type.equals("SE") && !type.equals("CO") && !type.equals("SU") && !type.equals("LI")){
                        System.out.println("Incorrect input! Please try again.");
                        continue;
                    }
                    notOk = false;
                }while(notOk);

                CarType carType = switch (type) {
                    case "SE" -> CarType.sedan;
                    case "CO" -> CarType.coupe;
                    case "SU" -> CarType.suv;
                    default -> CarType.limousine;
                };

                products.add(new Car(name, price, wheelNumber, doorNumber, seatNumber, carType));
                AuditCsvService.writeLogToCsv("Created-product Car " + carType);
            }
            else{
                System.out.print("Please enter the max load of the vehicle: ");
                double maxLoad = Utilities.readDoubleInInterval(scanner, 0, 200000);
                System.out.println("Please enter the type of utility vehicle - VA (Van), BU (Bus), TR (Truck)");
                notOk = true;
                do{
                    type = scanner.next().trim();
                    if(!type.equals("VA") && !type.equals("BU") && !type.equals("TR")){
                        System.out.println("Incorrect input! Please try again.");
                        continue;
                    }
                    notOk = false;
                }while(notOk);

                UtilityType utilityType;
                if(type.equals("VA"))
                    utilityType = UtilityType.van;
                else if (type.equals("BU"))
                    utilityType = UtilityType.bus;
                else
                    utilityType = UtilityType.truck;

                products.add(new UtilityVehicle(name, price, wheelNumber, doorNumber, seatNumber, maxLoad, utilityType));
                AuditCsvService.writeLogToCsv("Created-product UtilityVehicle " + utilityType);
            }
        }
    }

    /** Prints all product names along with every index in the product collection.
     *
     */
    public static void printNamesAndIndexes(){
        for(int index = 0; index < products.getList().size(); index++)
            System.out.print((index + 1) + ". " + products.getList().get(index).getName() + "\n");
    }

    public static void deleteProduct(Scanner scanner) throws Exception {
        System.out.println("Deleting a client.\n");
        printNamesAndIndexes();
        System.out.print("Please enter an index to delete (or 0 to cancel):");
        int toDeleteIndex = Utilities.readIntInInterval(scanner, 0, products.getList().size());
        if(toDeleteIndex != 0){
            String productId = products.getList().get(toDeleteIndex - 1).getId();
            AuditCsvService.writeLogToCsv("Deleted-product id - " + productId);
            products.delete(productId); //subtract one bc the printed list is 1-indexed
        }
    }

    public static void adjustStock(Scanner scanner) throws Exception{
        System.out.println("Adjusting a product's stock:");
        printAllProducts();
        System.out.print("Please enter the index of a merchandise-type product (or 0 to cancel):");
        int index = Utilities.readIntInInterval(scanner, 0, products.getList().size());

        if(index != 0) {
            Product product = products.getList().get(index - 1);
            while (Vehicle.class.isAssignableFrom(product.getClass())) {
                System.out.println("You have entered the index of a vehicle. Please select merchandise!");
                index = Utilities.readIntInInterval(scanner, 0, products.getList().size());
            }
            System.out.print("Please enter a new stock: ");
            int stock = Utilities.readIntInInterval(scanner, 0, Integer.MAX_VALUE);
            AuditCsvService.writeLogToCsv("Modified-stock id - " + product.getId());
            setStock(product, stock);
        }
    }

    public static void createDiscount(Scanner scanner) throws Exception{
        System.out.println("Creating a discount:");
        printAllProducts();

        System.out.print("Please enter the index of a product (or 0 to cancel):");
        int index = Utilities.readIntInInterval(scanner, 0, products.getList().size());

        if(index != 0){
            Product product = products.getList().get(index - 1);
            System.out.print("Please enter a discount percentage:");
            double discount = Utilities.readDoubleInInterval(scanner, 0, 100);
            setDiscount(product, discount);
            AuditCsvService.writeLogToCsv("Created-discount id - " + product.getId());
        }
    }

    public static void printMerchandiseWithHighestStock(){
        System.out.println("Printing the merchandise with the highest stock:");
        try {
            System.out.println(getMerchandiseWithHighestStock());
            AuditCsvService.writeLogToCsv("Printed-merchandise-with-highest-stock");
        }
        catch (Exception e){
            System.out.println("\tThere is no merchandise in the product list!");
        }
    }

    /** Prints products ordered by given criteria
     *
     * @param type - should be "discount" or "price"
     * @throws Exception - if the sort type is not one of the options
     */
    public static void printProductsOrdered(String type) throws Exception{
        System.out.println("Printing products ordered by " + type);
        if(type.equals("discount")) {
            printProductList(getProductsOrderedByDiscount());
        }
        else if(type.equals("price")) {
            printProductList(getProductsOrderedByPrice());
        }
        else
            throw new Exception("Incorrect sort type!");

        AuditCsvService.writeLogToCsv("Printed-products-ordered-by-" + type);
    }
}
