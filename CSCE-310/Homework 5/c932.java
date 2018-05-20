import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.*;

public class c932
{
	public static List<String> ShipName = new ArrayList<String>();
	public static List<String> ShipYear = new ArrayList<String>();
	
	public static void main(String [] args){
		String DBLocation = "database-new.cse.tamu.edu"; //The host 
		String DBname = ""; //Generally your CS username or username-text like explained above
		String DBUser = ""; //CS username
		String DBPass = ""; //password setup via CSNet for the MySQL database
		String className = "", type = "", country = "", numGuns = "", bore = "", displacement = "";
		
		Connection conn = null;
		try
		{
		Scanner sc = new Scanner(System.in);	
		System.out.print("Username: ");
		DBUser = sc.nextLine();
		System.out.print("Password: ");
		DBPass = sc.nextLine();
		System.out.print("Database: ");
		DBname = sc.nextLine();
			
		String connectionString = "jdbc:mysql://"+DBLocation+"/"+DBname;
		Class.forName ("com.mysql.jdbc.Driver").newInstance();
		conn = DriverManager.getConnection(connectionString, DBUser, DBPass);
		System.out.println ("\n---Database connection established---\n");
		
		System.out.println ("Please input a name of a class");
		className = sc.nextLine();
		System.out.println("User requested class: " + className);
		System.out.println("Please input the attributes in their respective order: type, country, numGuns, bore, displacement.");
		System.out.print("Type: ");
		type = sc.nextLine();
		System.out.print("Country: ");
		country = sc.nextLine();
		System.out.print("numGuns: ");
		numGuns = sc.nextLine();
		System.out.print("Bore: ");
		bore = sc.nextLine();
		System.out.print("Displacement: ");
		displacement = sc.nextLine();
		
		Statement st = conn.createStatement();
		
		st.executeUpdate("INSERT INTO classes VALUES ('" + className + "','" + type + "','" + country 
						+ "'," + numGuns + "," + bore + "," + displacement + ");");
		
		boolean loop = true;
		while(loop)
		{
			System.out.println("Please input the name and year of ships for the class: " + className);
			
			System.out.print("Name: ");
			String name = sc.nextLine();
			ShipName.add(name);
			
			System.out.print("Year: ");
			String year = sc.nextLine();
			ShipYear.add(year);
			
			st.executeUpdate("INSERT INTO ships VALUES ('" + name + "','" + className + "'," + year + ");");
			
			System.out.println("Insert Successful");
			
			System.out.print("Add more ships? (Y/N): ");
			String repeat = sc.nextLine();
			
			if (repeat.equals("N") || repeat.equals("n"))
				loop = false;
		}
		
		System.out.println(ShipName.toString());
		System.out.println(ShipYear.toString());

		}
		catch (Exception e)
		{
		System.out.println("Connection Issue: " + e.getMessage());
		}
	}
}