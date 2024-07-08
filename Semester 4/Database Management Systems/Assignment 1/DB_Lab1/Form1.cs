using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data;
using System.Data.SqlClient;
using System;

namespace WindowsFormsExample
{
    public partial class Form1 : Form
    {
        private SqlConnection connection;
        private SqlDataAdapter adapterBosses; //parent table : Bosses
        private SqlDataAdapter adapterShops; //child table : Shops

        private DataSet dataSet;

        private SqlCommandBuilder commandBuilder;
        private string queryBosses;
        private string queryShops;

        public Form1()
        {
            InitializeComponent();
            this.dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView2.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            this.Load += new EventHandler(this.Form1_Load);
            this.button1.Click += new EventHandler(this.button1_Click); // connect button1 with button1_Click event handler
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            FillData();
        }

        void FillData()
        {
            //connection to DBMS
            connection = new SqlConnection(getConnectionString());
            connection.Open();

            //fill the queries for the parent and the child tables
            queryBosses = getBossesQuery();
            queryShops = getShopsQuery();

            //init the adapters
            adapterBosses = new SqlDataAdapter(queryBosses, connection);
            adapterShops = new SqlDataAdapter(queryShops, connection);

            dataSet = new DataSet();
            adapterBosses.Fill(dataSet, "Bosses"); //fill with data set + name of the table
            adapterShops.Fill(dataSet, "Shops"); //fill with data set + name of the table

            //this will include all IUD operations
            commandBuilder = new SqlCommandBuilder(adapterBosses);

            //create a new table => parent-child relationship between tables Bosses and Shops
            dataSet.Relations.Add("Bosses_Shops",
                dataSet.Tables["Bosses"].Columns["boss_id"],
                dataSet.Tables["Shops"].Columns["boss_id"]);
            this.dataGridView1.DataSource = dataSet.Tables["Bosses"];
            this.dataGridView2.DataSource = this.dataGridView1.DataSource; //link the 2 tables through the foreign key
            this.dataGridView2.DataMember = "Bosses_Shops"; //binds dataGridView2 to display only the children of the selected parent
                                                            //in dataGridView1, based on the relationship (boss_id, common column)

        }
        string getConnectionString()
        {
            return "Data Source=Mingea;Initial Catalog=Sem2_ShoeMarket;Integrated Security=true;";
        }

        string getBossesQuery()
        {
            return "SELECT * FROM Bosses";
        }

        string getShopsQuery()
        {
            return "SELECT * FROM Shops";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            adapterShops.Update(dataSet, "Shops");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                DataTable shopsTable = dataSet.Tables["Shops"];
                DataTable changes = shopsTable.GetChanges();
                //check if changes were performed on the child table
                if (changes != null)
                {
                    commandBuilder = new SqlCommandBuilder(adapterShops);
                    adapterShops.Update(dataSet, "Shops");
                    MessageBox.Show("Successful I/U/D operation!");
                }
                else
                {
                    MessageBox.Show("I/U/D operations must be performed only in the child table!");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error!");
            }

        }

        private void button3_Click(object sender, EventArgs e)
        {

        }
    }
}
