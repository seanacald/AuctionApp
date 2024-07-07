package tests;

import backend.Backend;
import backend.Item;
import backend.User;
import io.FileParser;
import backend.Constants;
import org.junit.Test;
import static org.junit.Assert.*;
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

import java.io.File;
import java.util.Vector;

/*
 * Please compile from the root directory of this project.
 * These instructions were written for a Linux machine.
 * If you are on Linux, you can copy and paste these commands into the terminal to run the tests.
 * Or, you could use `make` to compile, and `make runtests` to run the tests.
 * To compile the backend:
 * 	$ javac backend/*.java
 * To compile this file:
 * 	$ javac -d tests/output/ -cp .:./lib/junit-4.12.jar tests/UserTests.java
 * To run the tests:
 * 	$ java -cp .:/:tests/output/:./lib/hamcrest-core-1.3.jar:./lib/junit-4.12.jar org.junit.runner.JUnitCore tests.UserTests
 */

public class Tests {

	// Tests setUsers() and getUsers() statement coverage.
	@Test
	public void testGetUsers() {
		Backend backend = new Backend();
		backend.setUsers(new Vector<String>());
		assertTrue(backend.getUsers().size() == 0);
	}

	// Tests that addNewUser() can add a user.
	@Test
	public void usersVectorNotEmptyAfterAdd() {
		Backend backend = new Backend();
		backend.setUsers(new Vector<String>());
		backend.addNewUser("01 a               FS 000000.00");
		assertTrue(backend.getUsers().size() == 1);
	}

	// Tests that addNewUser() does not add a user if they already exist.
	@Test
	public void doNotAddDuplicateUser() {
		Backend backend = new Backend();
		backend.setUsers(new Vector<String>());
		backend.addNewUser("01 a               FS 000000.00");
		backend.addNewUser("01 a               FS 000000.00");
		assertTrue(backend.getUsers().size() == 1);
	}

	// Tests statement coverage for updateUser().
	@Test
	public void testUpdateUser() {
		Backend backend = new Backend();
		backend.setUsers(new Vector<String>());
		backend.addNewUser("01 a               FS 000000.00");
		backend.updateUser("06 a               FS 000000.00");
		assertTrue(backend.getUsers().get(0).equals("a               FS 000000.00"));
	}

	// Tests statement coverage for refundUser().
	@Test
	public void testRefundUser() {
		Backend backend = new Backend();
		backend.setUsers(new Vector<String>());
		backend.addNewUser("01 a               FS 000000.00");
		backend.addNewUser("01 b               FS 000000.01");
		backend.refundUser("05 a               b               000000.01");
		String buyerCredit = backend.getUsers().get(0).substring(19, 28);
		String sellerCredit = backend.getUsers().get(1).substring(19, 28);
		assertTrue(buyerCredit.equals("000000.01") && sellerCredit.equals("000000.00"));
	}

	// Tests statement coverage for deleteUser().
	@Test
	public void testDeleteUser() {
		Backend backend = new Backend();
		backend.setUsers(new Vector<String>());
		backend.addNewUser("01 a               FS 000000.00");
		backend.deleteUser("06 a               FS 000000.00");
		assertTrue(backend.getUsers().size() == 0);
	}
	
	// Tests statement coverage for addItem().
	@Test
	public void testAddItem() {
		Backend backend = new Backend();
		backend.setItems(new Vector<String>());
		backend.addNewItem("03 a                         a               001 000.00");
		assertTrue(backend.getItems().size() == 1);
	}

	// Tests statement coverage for updateItem().
	@Test
	public void testUpdateItem() {
		Backend backend = new Backend();
		backend.setItems(new Vector<String>());
		backend.addNewItem("03 a                         a               001 000.00");
		backend.updateItem("04 a                         a               a               000.01");
		assertTrue(backend.getItems().size() == 1);
	}

	// Tests statement coverage for deleteItem().
	@Test
	public void testDeleteItem() {
		Backend backend = new Backend();
		backend.setItems(new Vector<String>());
		backend.addNewItem("03 a                         a               001 000.00");
		backend.deleteItem("a              ");
		assertTrue(backend.getItems().size() == 0);
	}

	// Tests statement coverage for endBid() if the item does not have a bidder.
	@Test
	public void testEndBidWithoutBidder() {
		Item item = new Item("03 a                         a               001 000.00");
		Backend backend = new Backend();
		backend.setUsers(new Vector<String>());
		backend.endBid(item);
		assertTrue(backend.getUsers().size() == 0);
	}

	// Tests statement coverage for endBid() if the item has a bidder.
	@Test
	public void testEndBidWithBidder() {
		Item item = new Item("03 a                         a               001 000.01");
		item.setBidder("a              ");

		Backend backend = new Backend();
		backend.setUsers(new Vector<String>());
		backend.addNewUser("01 a               FS 999999.99");

		backend.endBid(item);
		assertTrue(backend.getUsers().get(0).substring(19, 28).equals("999999.98"));
	}

	// Tests statement coverage for the User constructor.
	@Test
	public void testUserConstructor() {
		User user1 = new User("a               FS 000000.00"); // if given a string from the current user accounts
		User user2 = new User("01 a               FS 000000.00"); // if given a transaction to create a user
		User user3 = new User("a              "); // if given just a username
		assertTrue(user1.getUsername().equals("a              "));
		assertTrue(user2.getUsername().equals("a              "));
		assertTrue(user3.getAccountType() == null);
	}

	// Tests statement coverage for the User toString() function.
	@Test
	public void testUserToString() {
		String userString = "a               FS 000000.00";
		User user = new User(userString);
		assertTrue(user.toString().equals(userString));
	}

	// Decision coverage for addNewUser()
	@Test
	public void decisionCoverage() {
		Backend backend = new Backend();
		backend.setUsers(new Vector<String>());
		backend.addNewUser("01 a               FS 000000.00"); // Does not enter the loop
		backend.addNewUser("01 a               FS 000000.00"); // If statement is true
		backend.addNewUser("01 b               FS 000000.00"); // If statement is false
	}

	// Loop coverage for addNewUser()
	@Test
	public void loopCoverage() {
		Backend backend = new Backend();
		backend.setUsers(new Vector<String>());
		backend.addNewUser("01 a               FS 000000.00"); // Execute body zero times
		backend.addNewUser("01 b               FS 000000.00"); // Execute body once
		backend.addNewUser("01 c               FS 000000.00"); // Execute body twice
		
		// Execute body many times
		backend.addNewUser("01 d               FS 000000.00"); 
		backend.addNewUser("01 e               FS 000000.00");
		backend.addNewUser("01 f               FS 000000.00");
		backend.addNewUser("01 g               FS 000000.00");
		backend.addNewUser("01 h               FS 000000.00");
    }
    
    /* FileParser.java */
    
    // Test statement coverage for writeFile
    @Test
    public void testWriteFile() throws FileNotFoundException {
        Vector<String> data = new Vector<String>();
        data.add("Doug Dimmadone owner of the Dimmsdale Dimmadome");
        FileParser.writeFile(Constants.TEST_FILE, data);

        File file = new File(Constants.TEST_FILE);
        Scanner reader = new Scanner(file);
        String line = reader.nextLine();
        reader.close();
        assertEquals(line, data.get(0));
    }

    // Statement coverage for getFileInfo
    @Test 
    public void testGetFileInfo() throws FileNotFoundException {
        Vector<String> data = new Vector<String>();
        PrintWriter pw = new PrintWriter(Constants.TEST_FILE);

        data.add("Doug Dimmadone owner of the Dimmsdale Dimmadome");
        pw.println(data.get(0));
        pw.flush();
        pw.close();

        Vector<String> returnedData = FileParser.getFileInfo(Constants.TEST_FILE);
        assertEquals(returnedData.get(0), data.get(0));
        
    }
  
	//test that item constructor correctly takes in a advertise item string
	@Test
	public void itemAdvertise() {
		String s = "03 Dragon Scimmy             TestUser        013 000099";
		String e = "Dragon Scimmy             TestUser                        013 000099";
		Item item = new Item(s);
		assertTrue(item.toString().equals(e));
	}

	//test that item constructor correctly takes in a bid item string

	@Test
	public void itemBid() {
		String s = "04 apple                     TestUser        IsAdmin         006.00";
		String e = "apple                     TestUser        IsAdmin             006.00";
		Item item = new Item(s);
		assertTrue(item.toString().equals(e));
	}

	//test that item constructor correctly takes in a basic item string
	@Test
	public void itemBlank() {
		String s = "testItem                  testSeller      testBidder      000 001.00";
		Item item = new Item(s);
		assertTrue(item.toString().equals(s));
	}

	//test that isEndAuctionDate returns false if an auction has ended
	@Test
	public void auctionDone() {
		String s = "testItem                 testSeller        testBidder     000 001.00";
		Item item = new Item(s);
		assertFalse(item.isEndAuctionDate());
	}

	//test that isEndAuctionDate returns true if an auction hasnt ended
	@Test
	public void auctionNotDone() {
		String s = "testItem                 testSeller        testBidder     019 001.00";
		Item item = new Item(s);
		assertTrue(item.isEndAuctionDate());
	}

//test that the UpdateDaysRemaining funciton correctly updates the string
	@Test
	public void testUpdateDaysRemaining() {
		String s = "testItem                 testSeller        testBidder     019 001.00";
		Item item = new Item(s);
		item.updateDaysRemaining();
		assertTrue(item.getDays().equals("018"));
	}

	//test that toString correctly outputs the item details in a string
	@Test
	public void testToString() {
		String s = "toStringItem              testSeller      testBidder      000 001.00";
		Item item = new Item(s);
		assertTrue(item.toString().equals(s));
	}
}
