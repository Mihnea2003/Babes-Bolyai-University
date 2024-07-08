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
        private SqlDataAdapter adapterClients; 
        private SqlDataAdapter adapterMedicalImages; 

        private DataSet dataSet;

        private SqlCommandBuilder commandBuilder;
        private string queryClients;
        private string queryMedicalImages;

        public Form1()
        {
            InitializeComponent();
            this.dgvClients.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            this.dgvMedicalImages.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            this.Load += new EventHandler(this.Form1_Load);
            this.button1.Click += new EventHandler(this.button1_Click);
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
            queryClients = getClientsQuery();
            queryMedicalImages = getMedicalImagesQuery();

            //init the adapters
            adapterClients = new SqlDataAdapter(queryClients, connection);
            adapterMedicalImages = new SqlDataAdapter(queryMedicalImages, connection);

            dataSet = new DataSet();
            adapterClients.Fill(dataSet, "Clients"); 
            adapterMedicalImages.Fill(dataSet, "MedicalImages"); 

            
            commandBuilder = new SqlCommandBuilder(adapterClients);

            
            dataSet.Relations.Add("Clients_MedicalImages",
                dataSet.Tables["Clients"].Columns["c_id"],
                dataSet.Tables["MedicalImages"].Columns["c_id"]);
            this.dgvClients.DataSource = dataSet.Tables["Clients"];
            this.dgvMedicalImages.DataSource = this.dgvClients.DataSource; 
            this.dgvMedicalImages.DataMember = "Clients_MedicalImages"; 
                                                            

        }
        string getConnectionString()
        {
            return "Data Source=Mingea;Initial Catalog=Dental Cabinet;Integrated Security=true;";
        }

        string getClientsQuery()
        {
            return "SELECT * FROM Clients";
        }

        string getMedicalImagesQuery()
        {
            return "SELECT * FROM MedicalImages";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            adapterMedicalImages.Update(dataSet, "MedicalImages");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                DataTable MedicalImagesTable = dataSet.Tables["MedicalImages"];
                DataTable changes = MedicalImagesTable.GetChanges();
                //check if changes were performed on the child table
                if (changes != null)
                {
                    commandBuilder = new SqlCommandBuilder(adapterMedicalImages);
                    adapterMedicalImages.Update(dataSet, "MedicalImages");
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

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
