namespace Web_practic_sample2024.Models
{
    public class Project
    {
        public int Id { get; set; }
        public int ProjectManagerID { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public string Members { get; set; }
    }
}
