# CS124PocketLawyer
An Ohlone CS124 Project focused on informing a user about law enforcement and government  agencies.

Current ideas  here:
1) (Darcie) Decision tree for Q&A in emergency situations.
   - Fast and simple, gives quick resources for those in need.
   - Must give a disclaimer that this is a tool to be used and not something to be used in court.
  
     
2) (Darcie) Adding historical, anonymized data of reported activity counts by county || Official statistic or reports of recent ICE harassment or of crimes.
   - Most of this info would be crowdfunded so it is unverified and time-sesitive.
   - The most we can do is report official statistics or reports and having a sorting algorithms we can view the most recent official sighting as well as what county and city they have frequent reports in.
  

3) (Kenshin) Legal Document Parsing Engine
   - Objective:
        To assist users in parsing through the specific language of citations or government notices, translating dense legal jargon into plain English, or going to relevant articles quickly.
   - Technical Implementation:
        String Matching Algorithms: Application of algorithms (Gemini recommends Boyer-Moore or Knuth-Morris-Pratt) to scan uploaded text or manual input for specific legal clauses or mandatory disclosure requirements.
   - Hash Table Mapping: Used to map identified "red flags" or mandatory phrases directly to their plain-English explanations and corresponding legal rights.
   For example, we can have a GUI app that can help somebody quite quickly.
     1. Let's say a person uses Darcie’s "Emergency Q&A" and presses the button or says yes to terminal for: "Is a police officer asking to see your ID?"
     2. The User taps or inputs "Yes."
     3. The Parser logic instantly pulls the specific "Leaf Node" from the Penal Code Tree related to "Failure to Identify."
     4. The UI displays a simple "TL;DR" summary: "In California, you generally do not have to show ID unless you are being detained or are driving."
     5. Below that summary, there is a button: "Read the Full Law." Because of the tree, that button takes them exactly to Section 148, not just the top of the page.- 
- Possible tree structure:
   - The Root (Level 0): The entire Code (e.g., "California Penal Code").
   - The Branches (Level 1 & 2): These nodes are the containers. A node that contains links to sub-topics like "Search and Seizure" or "Right to Counsel" instead of the full law.
   - The Leaves (Level 3+): These are the leaf nodes. They contain the actual string data (the text of the law) and the metadata (the law number, the date it was passed).
- The bottom line idea is that we try to create a search engine that parses the entire code and lets you go to the specific chapter or give a tldr very quickly.

A single node can have the name of the node like "Article 4: something", a type such as the hierachy level "Article" or "Chapter", the children are more specific nodes like "Section: 2102" or "Section: 2104" and the LEAF NODES will have the actual text like "In California, you generally do not have to show ID unless you are being detained or are driving".

     
