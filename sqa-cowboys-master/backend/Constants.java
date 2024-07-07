package backend;
/**
 * Constant class.
 * Holds useful constants to be used throughout the application
 * 
 * @author Luke Tran, Sean Caldwell, Calvin Lapp
 * @since March 26th, 2020
 * @version 1.0.1
 * @name Constants.java
 */
public final class Constants {

        private Constants() {
            // don't allow instantiation 
        }

        /* File names */
        public static final String CURRENT_USER_ACCOUNTS_FILE = "current_user_accounts_file.txt";
        public static final String DAILY_TRANSACTION_FILE = "daily_transaction_file.txt";
        public static final String AVAILABLE_ITEMS_FILE = "available_items_file.txt";
        public static final String TEST_FILE = "test_file.txt";


        /* Transaction codes */
        public static final String ADD_NEW_USER = "01";
        public static final String DELETE = "02";
        public static final String ADD_NEW_ITEM = "03";
        public static final String BID = "04";
        public static final String REFUND = "05";
        public static final String ADD_CREDIT = "06";
        public static final String END_OF_SESSION = "00";

        /* Items */
        public static final int ITEM_NAME_LENGTH = 25;
        public static final int NEW_ITEM_ENTRY_LENGTH = 55;
        public static final int BID_ITEM_ENTRY_LENGTH = 67;

        /* Users */
        public static final int USERNAME_MAX_LENGTH = 15;
        public static final int CURRENT_USER_LENGTH = 28;
        public static final int ADD_UPDATE_USER_LENGTH = 31;
        public static final double MAX_BALANCE = 999999.99;
}