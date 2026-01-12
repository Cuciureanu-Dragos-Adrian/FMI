package services;

import collections.ClientsCollection;
import collections.ProductsCollection;
import models.clients.Client;
import models.clients.PF;
import models.clients.PJ;
import models.products.Merchandise;
import models.products.Product;

import java.util.List;
import java.util.Scanner;

public class ClientService {
    private static final ClientsCollection clients = ClientsCollection.getCollection();
    private static final ProductsCollection products = ProductsCollection.getCollection();

    /** Allows a client to purchase a product.
     *
     * @param client the client that tries to purchase
     * @param product the product that is being purchased
     * @param quantity the quantity
     * @throws Exception - if either client or product does not exist, the client does not have enough funds, or the quantity is incorrect
     */
    private static void purchaseProduct(Client client, Product product, int quantity) throws Exception {
        double totalCost = quantity * product.getPrice() * (100 + client.getVAT()) / 100;

        if(!clients.idExists(client.getId()))
            throw new Exception("Client does not exist!");
        if(!products.idExists(product.getId()))
            throw new Exception("Product does not exist!");
        if(client.getFunds() < totalCost) //check if client has enough funds
            throw new Exception("Client does not have enough funds!");
        if(quantity < 0)
            throw new Exception("Quantity too low!");

        // check stock and demand
        if(Merchandise.class.isAssignableFrom(product.getClass())){  // merchandise
            Merchandise merch = (Merchandise) product;
            if(quantity > merch.getStock())
                throw new Exception("Quantity too high!");
        }
        else{ // vehicle
            if(quantity != 1)
                throw new Exception("Quantity must be 1 for vehicles!");
        }

        client.setFunds(client.getFunds() - totalCost);
        client.addProduct(product, quantity);
        clients.update(client);
        ProductService.subtractStock(product, quantity); // this method calls an update
    }

    public static void printAllClients() throws Exception{
        System.out.print("\nPrinting clients\n");
        printClientList(clients.getList());
        AuditCsvService.writeLogToCsv("Printed-clients");
    }

    private static void printClientList(List<Client> list){
        for(int idx = 0; idx < list.size(); idx++){
            System.out.print((idx + 1) + ". " + list.get(idx) + "\n");
        }
    }

    /** Reads and creates a new Client object.
     *
     */
    public static void readClient(Scanner scanner) throws Exception {
        System.out.println("Reading a client\n");
        System.out.println("Please input the client's funds:");

        double funds = Utilities.readDoubleInInterval(scanner, 0, Integer.MAX_VALUE);

        System.out.println("Please enter the type of client - PF (Persoana Fizica), PJ (Persoana juridica): ");

        boolean notOk = true;

        String type;
        do{
            type = scanner.next().trim();
            if(!type.equals("PF") && !type.equals("PJ")){
                System.out.println("Incorrect input! Please try again.");
                continue;
            }
            notOk = false;
        }while(notOk);

        if(type.equals("PF")) {
            System.out.print("Please input the last name: ");
            String lastName = scanner.next().trim();
            System.out.print("Please input the first name: ");
            String firstName = scanner.next().trim();

            System.out.print("Please input the PNC (Personal Numeric Code, contains only digits): ");
            notOk = true;
            String PNC;
            do{
                PNC = scanner.next().trim();
                if(!Utilities.containsOnlyDigits(PNC)){
                    System.out.println("Input must contain only digits! Please try again.");
                    continue;
                }
                notOk = false;
            }while(notOk);

            //add new PF to list
            clients.add(new PF(firstName, lastName, PNC, funds));
            AuditCsvService.writeLogToCsv("Create-client PF");
        }
        else{
            System.out.print("Please input the business' name: ");
            String name = scanner.next().trim();

            System.out.print("Please input the FIC (Fiscal Identification Code, contains only digits): ");
            notOk = true;
            String FIC;
            do{
                FIC = scanner.next().trim();
                if(!Utilities.containsOnlyDigits(FIC)){
                    System.out.println("Input must contain only digits! Please try again.");
                    continue;
                }
                notOk = false;
            }while(notOk);


            AuditCsvService.writeLogToCsv("Create-client PJ");
            //add new PJ to list
            clients.add(new PJ(name, FIC, funds));
        }
    }

    /** Prints all client names along with every index in the client collection.
     *
     */
    public static void printNamesAndIndexes(){
        for(int index = 0; index < clients.getList().size(); index++)
            System.out.print((index + 1) + ". " + clients.getList().get(index).getFullName() + "\n");
    }

    public static void deleteClient(Scanner scanner) throws Exception {
        System.out.println("Deleting an employee.\n");
        printNamesAndIndexes();
        System.out.print("Please enter an index to delete (or 0 to cancel): ");
        int toDeleteIndex = Utilities.readIntInInterval(scanner, 0, clients.getList().size());
        if(toDeleteIndex != 0){
            String clientId = clients.getList().get(toDeleteIndex - 1).getId();
            AuditCsvService.writeLogToCsv("Delete-client id - " + clientId);
            clients.delete(clientId); //subtract one because the printed list is 1-indexed
            System.out.println("Delete successful!");
        }
    }

    public static void executeSale(Scanner scanner) throws Exception{
        System.out.println("Executing a sale:");
        printNamesAndIndexes();
        System.out.print("Please select a client (or 0 to cancel):");
        int clientIndex = Utilities.readIntInInterval(scanner, 0, clients.getList().size());
        if(clientIndex != 0) {
            Client client = clients.getList().get(clientIndex - 1);
            ProductService.printAllProducts();

            System.out.print("Please select a product (or 0 to cancel):");
            int productIndex = Utilities.readIntInInterval(scanner, 0, products.getList().size());
            if (productIndex == 0)
                return;
            Product product = products.getList().get(productIndex - 1);

            int quantity = 1;
            //if a vehicle was selected, quantity is by default 1, else it needs to be read
            if (Merchandise.class.isAssignableFrom(products.getList().get(productIndex - 1).getClass())){
                System.out.print("Please select a quantity: ");
                Merchandise merch = (Merchandise) product;
                quantity = Utilities.readIntInInterval(scanner, 0, merch.getStock());
            }

            double priceWithVAT = quantity * product.getPrice() * (100 + client.getVAT()) / 100;
            if (client.getFunds() < priceWithVAT)
                System.out.print("Client does not have enough funds!");
            else {
                AuditCsvService.writeLogToCsv("Product-purchase client - " + client.getId() + " product - " + product.getId() + " quantity - " + quantity);
                purchaseProduct(client, product, quantity);
            }
        }
    }
}
