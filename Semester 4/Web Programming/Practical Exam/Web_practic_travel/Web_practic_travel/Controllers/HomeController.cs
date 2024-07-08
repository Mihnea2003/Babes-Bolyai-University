using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;
using Web_practic_travel.Models;

namespace Web_practic_travel.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;

        public HomeController(ILogger<HomeController> logger)
        {
            _logger = logger;
        }
        public IActionResult Choose()
        {
            
            _logger.LogInformation($"UserName: {ViewData["UserName"]}, Date: {ViewData["date"]}, Destination City: {ViewData["destination_city"]}");
            return View();
        }
        [HttpPost]
        public IActionResult SetUser(string userName,string date,string destination_city)
        {
            TempData["UserName"] = userName;
            TempData["date"] = date;
            TempData["destination_city"] = destination_city;
            TempData.Keep("UserName");
            TempData.Keep("date");
            TempData.Keep("destination_city");
            return RedirectToAction("Choose","Home");
        }
        public ActionResult Flights()
        {
     
            return RedirectToAction("Index", "Flights");
        }

        // Redirect to Hotels
        public ActionResult Hotels()
        {
            
            return RedirectToAction("Index", "Hotels");
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
