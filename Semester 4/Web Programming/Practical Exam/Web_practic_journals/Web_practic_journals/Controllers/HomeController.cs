using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using Web_practic_journals.Models;
using System.Linq;
using System.Diagnostics;
using Web_practic_journals.Data;

namespace Web_practic_journals.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;
        private readonly ApplicationDbContext _context;

        public HomeController(ILogger<HomeController> logger, ApplicationDbContext context)
        {
            _logger = logger;
            _context = context;
        }

        public IActionResult Index()
        {
            return View();
        }

        // Method to set user name using TempData
        [HttpPost]
        public IActionResult SetUser(string userName)
        {
            TempData["UserName"] = userName;
            return RedirectToAction("SelectJournal");
        }

        // Display a list of journals to select from
        public IActionResult SelectJournal()
        {
            ViewData["UserName"] = TempData["UserName"];
            TempData.Keep("UserName"); // Keep the value for the next request
            return View(_context.Journals.ToList());
        }

        // Method to handle journal selection or creation
        [HttpPost]
        public IActionResult SelectJournal(string journalName)
        {
            var journal = _context.Journals.FirstOrDefault(j => j.Name == journalName);

            if (journal == null)
            {
                journal = new Journal { Name = journalName };
                _context.Journals.Add(journal);
                _context.SaveChanges();
            }

            TempData["JournalId"] = journal.Id;
            TempData.Keep("UserName"); // Keep the value for the next request
            return RedirectToAction("UserArticles");
        }

        // Display the articles for the current user in the selected journal
        public IActionResult UserArticles()
        {
            string userName = TempData["UserName"] as string;
            int? journalId = TempData["JournalId"] as int?;

            if (journalId == null) return RedirectToAction("SelectJournal");

            var articles = _context.Articles
                .Where(a => a.User == userName && a.JournalId == journalId)
                .ToList();
            TempData.Keep("UserName"); // Keep the value for the next request
            TempData.Keep("JournalId"); // Keep the value for the next request
            return View(articles);
        }

        // Display the form to add a new article
        public IActionResult AddArticle()
        {
            TempData.Keep("UserName"); // Keep the value for the next request
            TempData.Keep("JournalId"); // Keep the value for the next request
            return View();
        }

        // Handle adding a new article
        [HttpPost]
        public IActionResult AddArticle(string summary)
        {
            string userName = TempData["UserName"] as string;
            int? journalId = TempData["JournalId"] as int?;

            if (journalId == null) return RedirectToAction("SelectJournal");

            var article = new Article
            {
                User = userName,
                JournalId = journalId.Value,
                Summary = summary,
                Date = DateTime.Now
            };

            _context.Articles.Add(article);
            _context.SaveChanges();

            NotifyNewArticle(article);

            TempData.Keep("UserName"); // Keep the value for the next request
            TempData.Keep("JournalId"); // Keep the value for the next request
            return RedirectToAction("UserArticles");
        }

        // Method to notify users about a new article
        private void NotifyNewArticle(Article article)
        {
            // Here you can add the code to notify the user about the new article.
            // This can be done using SignalR or other real-time communication methods.
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
