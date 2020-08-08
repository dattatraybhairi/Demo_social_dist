void find_uinque_pairs()
{
  // This function finds unique pairs of employee tags which breaches social distancing norms
  // Tag - > Gateway Packet Structure
  // Self Id (2 Bytes) + Tags in proximity (10 Bytes = 5 * 2 Bytes) + Battery Status = 13 Bytes
  
  uint8_t a = 0; // No. of valid tags in a packet
  uint8_t ID1_LB, ID1_HB, ID2_LB, ID2_HB;
  uint8_t unique_flag = 1;
  uint8_t p,q,r,s;
  
  for (uint8_t i = 0; i < 5; i++)
  {
    if (radioPktBuffer[4+i*2] != 0) // TagId_HB Can be 0  but LB can never be 0 (Tag Ids are given in that way) 
    a++;  
  }
  
  for (uint8_t i = 0; i < a; i++)
  {
    ID1_HB = radioPktBuffer[1];
    ID1_LB = radioPktBuffer[2];
    ID2_HB = radioPktBuffer[3+i*2];
    ID2_LB = radioPktBuffer[4+i*2];
    for (uint8_t j = 0; j < unique_count; j++)
    {
      p = unique_pair_data[j*data_per_tag];   //Stored "Tag 1" HB
      q = unique_pair_data[j*data_per_tag+1]; //Stored "Tag 1" LB
      r = unique_pair_data[j*data_per_tag+2]; //Stored "Tag 2" HB
      s = unique_pair_data[j*data_per_tag+3]; //Stored "Tag 2" LB
      if (ID1_HB == p || ID1_HB == r) // Check for higher byte match Tag 1
      {
        if (ID1_LB == q || ID1_LB == s) // Check for lower byte match Tag 1
        {
          if (ID2_HB == p || ID2_HB == r) // Check for higher byte match Tag 2
          {
            if (ID2_LB == q || ID2_LB == s) // Check for lower byte match Tag 2
            {
              unique_flag = 0;
              break;
            }
          }
        }
      }
    }
    if (unique_flag == 1)
    {
      unique_pair_data[unique_count*data_per_tag] = ID1_HB;
      unique_pair_data[unique_count*data_per_tag+1] = ID1_LB;
      unique_pair_data[unique_count*data_per_tag+2] = ID2_HB;
      unique_pair_data[unique_count*data_per_tag+3] = ID2_LB;
      unique_pair_data[unique_count*data_per_tag+4] = radioPktBuffer[13]; // Battery
      unique_pair_data[unique_count*data_per_tag+5] = radioPktBuffer[15]; // RSSI
      unique_pair_data[unique_count*data_per_tag+6] = radioPktBuffer[14]; // Alert
      unique_count++;
    }
  }

  //----------------------------------------- Adding Tag Health Data -------------------------------------
  unique_flag = 1;
  
  ID1_HB = radioPktBuffer[1];
  ID1_LB = radioPktBuffer[2];
  for (uint8_t j = 0; j < health_count; j++)
  {
    if (ID1_HB == health_data[j*7] && ID1_LB == health_data[j*7+1])
    unique_flag = 0;
  }
  if (unique_flag == 1)
  {
    health_data[health_count*data_per_tag] = ID1_HB;
    health_data[health_count*data_per_tag + 1] = ID1_LB;
    health_data[health_count*data_per_tag + 4] = radioPktBuffer[13]; // Battery
    health_data[health_count*data_per_tag + 5] = radioPktBuffer[15]; // RSSI
    health_data[health_count*data_per_tag + 6] = radioPktBuffer[14]; // Alert
    health_count++;
  }

}
