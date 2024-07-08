using Examen.Data;
using Examen.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Diagnostics;

namespace Examen.Controllers
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
        public IActionResult Start()
        {
            // Redirect to the new page
            return RedirectToAction("Login", "Home");
        }
        public IActionResult Login()
        {
            return View();
        }
        [HttpPost]
        public async Task<IActionResult> Login(string name, string document_name)
        {
            var author = await _context.Author.SingleOrDefaultAsync(a => a.Name == name);

            if (author != null)
            {
                var documentNames = author.documentList?.Split(',').Select(d => d.Trim()).ToList();
                if (documentNames != null && documentNames.Contains(document_name))
                {
                   
                        TempData["authorName"] = author.Name;
                        TempData.Keep("authorName");

                        return RedirectToAction("Index", "Documents");                
                }
                else
                {
                    var moviesNames = author.movieList?.Split(',').Select(d => d.Trim()).ToList();
                    if (moviesNames != null && moviesNames.Contains(document_name))
                    {
                        TempData["authorName"] = author.Name;
                        TempData.Keep("authorName");

                        return RedirectToAction("Index", "Documents");
                    }
                }
            }
            else
            {
                
                ModelState.AddModelError(string.Empty, "Invalid username or password");
            }
            return View();
        }
   
    public IActionResult Index()
        {
            return View();
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
